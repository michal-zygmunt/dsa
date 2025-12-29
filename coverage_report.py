#!/usr/bin/env python3

"""
  @file generate_coverage.py
  @brief This file contains Python script to run tests and generate coverage report
  @author Michal Zygmunt
  
  @copyright Copyright (c) 2025 Michal Zygmunt
  This project is distributed under the MIT License.
  See accompanying LICENSE.txt file or obtain copy at
  https://opensource.org/license/mit
"""

import argparse
from datetime import datetime
from enum import StrEnum
import os
from pathlib import Path
import platform
import subprocess
import sys

FILENAME_FRAGMENT = "test"

class Compiler(StrEnum):
    CLANG = "clang"
    GCC = "gcc"

class Tool(StrEnum):
    LCOV = "lcov"
    GCOVR = "gcovr"

def log(if_print : bool, data : any):
    if(if_print):
        print(data)


def abs_path_in_wsl(path : str, verbose = False):
    
    wsl_prefix_path = "/mnt/"

    # Windows based path,
    # wsl uses lower case letters for windows path
    if ':' in path:
        tokens = path.split(':')
        path = (wsl_prefix_path + str(tokens[0]).lower() + str(tokens[1])).replace("\\", '/')

    log(verbose, tokens)
    return path


def check_if_app_exists(executable_name : str, use_wsl = False, verbose = False) -> bool:
    args = [executable_name, "--version"]

    if use_wsl:
        args.insert(0, "wsl")

    try:
        result = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    except FileNotFoundError:
        print(str(executable_name) + " not found!")
        return False
    
    log(verbose, str(executable_name) + " found!")
    log(verbose, result.stdout)
    return True

def detect_tools(tool : str, verbose : bool) -> bool:
    use_wsl = False

    # check for clang
    if(check_if_app_exists("llvm-profdata", verbose=verbose) and check_if_app_exists("llvm-cov", verbose=verbose)):
        print("Clang tools found!")
    else:
        sys.exit("Clang tools not found! Make sure clang tools are added to system path.")

    # running script on Windows require wsl to use Linux tools
    if(platform.system() == "Windows"):
        if(check_if_app_exists("wsl", verbose=verbose)):
            print("WSL found!")
            use_wsl = True
        else:
            sys.exit("WSL not found! Generating coverage reports require use of Linux tools. Make sure WSL was set up.")
    
    # Linux native tools required to generate report
    if tool == Tool.LCOV:
        if(check_if_app_exists(Tool.LCOV, use_wsl=use_wsl, verbose=verbose)):
            print("lcov package found!")
        else:
            sys.exit("Linux tools not found! Make sure lcov package is installed.")

    if tool == Tool.GCOVR:
        if(check_if_app_exists(Tool.GCOVR, use_wsl=use_wsl, verbose=verbose)):
            print("gcovr package found!")
        else:
            sys.exit("Linux tools not found! Make sure gcovr package is installed.")

    return use_wsl
    

def clean_artifacts(start_path="."):
    for f in Path(start_path).rglob("*.profraw"):
        f.unlink()

    for f in Path(start_path).rglob("*.profdata"):
        f.unlink()

    for f in Path(start_path).rglob("*.lcov"):
        f.unlink()

    # TODO clean gcc coverage data when test apps are compiled by Python routine
    # for f in Path(start_path).rglob("*.gcno"):
    #     f.unlink()

    for f in Path(start_path).rglob("*.gcda"):
        f.unlink()

def find_files(file_pattern : str, extension : str, start_path="."):
    return [file for file in Path(start_path).rglob(extension) if file_pattern.lower() in file.stem.lower()]


def find_test_apps(start_path=".", verbose = False) -> list:
    if(platform.system() == "Windows"):
        test_apps = find_files(FILENAME_FRAGMENT, "*.exe", start_path)
    else:
        files_list = find_files(FILENAME_FRAGMENT, "*", start_path)
        
        test_apps = []
        for file in files_list:
            if (file.is_file() and os.access(file, os.X_OK)):
                test_apps.append(file)
    
    log(verbose, test_apps)

    if not test_apps:
        sys.exit("No test application found!")

    return test_apps


def run_test_apps(applications, compiler : str):
    for app in applications:
        print(f"Starting test: {app}")

        env = os.environ.copy()
        if compiler.lower() == Compiler.CLANG:
            # use individual names for profraw files
            profraw = app.with_suffix(".profraw").name
            env = os.environ.copy()
            env["LLVM_PROFILE_FILE"] = profraw

        # run test apps to generate instrumentation data for coverage report
        # profraw files for clang are generated near app executable
        subprocess.run(str(app), cwd=Path(app).parent, env=env, check=True)


def exclude_path(arguments : list, exclude_name : str):
    if exclude_name != "":
        arguments += ["--exclude", exclude_name]

    return arguments


def generate_profdata(start_path=".", verbose = False):
    print(f"Merge .profraw into .profdata")

    profraw_files = find_files(FILENAME_FRAGMENT, "*.profraw", start_path)
    if not profraw_files:
        sys.exit("No .profraw files found!")

    for profraw in profraw_files:
        args = ["llvm-profdata", "merge", "-sparse", f"{profraw}", "-o", f"{os.path.splitext(profraw)[0]}.profdata"]
        log(verbose, args)
        subprocess.run(args, check=True)


def generate_lcov(applications, start_path=".", verbose = False):
    print(f"Export .profdata to .lcov")

    profdata_files = find_files(FILENAME_FRAGMENT, "*.profdata", start_path)
    if not profdata_files:
        sys.exit("No .profdata files found! Exiting!")

    for app in applications:
        args = ["llvm-cov", "export", "--format=lcov", f"{app}", f"-instr-profile={os.path.splitext(app)[0]}.profdata"]
        log(verbose, args)
        with open(f"{os.path.splitext(app)[0]}.lcov", "w") as output_file:
            subprocess.run(args, check=True, stdout=output_file)


def generate_info_clang(start_path, coverage_report_dir : str, coverage_report_name : str,
                        use_wsl = False, verbose = False):
    print(f"Merge .lcov into .info")

    lcov_files = find_files(FILENAME_FRAGMENT, "*.lcov", start_path)
    if not lcov_files:
        sys.exit("No .profdata files found!")
    
    output_file = os.path.join(coverage_report_dir, coverage_report_name)
    args = ["lcov", "--function-coverage", "--branch-coverage"]

    if use_wsl:
        args.insert(0, "wsl")
        output_file = abs_path_in_wsl(output_file)

    for file in Path(start_path).rglob("*.lcov"):
        if FILENAME_FRAGMENT in file.stem.lower():
            line = str(Path(file).as_posix())
            # convert absolute Windows path to wsl
            if use_wsl:
                line = abs_path_in_wsl(line)
            args += ["-a"] + [line]    

    args += ["--output-file", output_file]
    log(verbose, args)
    subprocess.run(args, check=True)


def generate_info_gcc(start_path, coverage_report_dir : str, coverage_report_name : str,
                      use_wsl = False, verbose = False):

    print(f"Merge .gcda and .gcno into .info")

    gcda_files = find_files(FILENAME_FRAGMENT, "*.gcda", start_path)
    if not gcda_files:
        sys.exit("No .gcda files found!")

    gcno_files = find_files(FILENAME_FRAGMENT, "*.gcda", start_path)
    if not gcno_files:
        sys.exit("No .gcno files found!")
    
    output_file = os.path.join(coverage_report_dir, coverage_report_name)

    if use_wsl:
        args.insert(0, "wsl")
        output_file = abs_path_in_wsl(output_file)
    
    args = ["lcov", "--function-coverage", "--branch-coverage",
            "--capture", "--directory", start_path,
            "--no-external", "--output-file", output_file,
            # NOTE compiling with gcc -O1 flag prevents mismatch exception tag error for lcov
            # and following line can be disabled
            "--ignore-errors", "mismatch"
            ]
    log(verbose, args)
    subprocess.run(args, check=True)


def generate_info(start_path, compiler : str, coverage_report_dir : str, coverage_report_name : str,
                  use_wsl = False, verbose = False):
    
    if compiler == Compiler.CLANG:
        generate_info_clang(start_path, coverage_report_dir, coverage_report_name, use_wsl, verbose)

    elif compiler == Compiler.GCC:
        generate_info_gcc(start_path, coverage_report_dir, coverage_report_name, use_wsl, verbose)

    else:
        sys.exit(f"Unexpected compiler: {compiler}. Exiting!")

    # if wsl is used, file paths in info file needs to be prepended with /mnt/ prefix
    # and os separators needs to be updated for genhtml
    if use_wsl:
        with open(os.path.join(coverage_report_dir, coverage_report_name), 'r+', newline='\n') as output_file:
            data = output_file.readlines()
            output_file.seek(0)
            output_file.truncate(0)

            sf = "SF:"
            for line in data:
                if sf in line:
                    tokens = line.split(sf)
                    abs_path = abs_path_in_wsl(tokens[1])
                    line = sf + abs_path
                    log(verbose, line)

                output_file.write(line)


def generate_gcovr_report(start_path, coverage_report_dir : str, exclude_name : str,
                          use_wsl = False, verbose = False):
    
    print(f"Merge .gcda and .gcno into html report")

    gcda_files = find_files(FILENAME_FRAGMENT, "*.gcda", start_path)
    if not gcda_files:
        sys.exit("No .gcda files found!")

    gcno_files = find_files(FILENAME_FRAGMENT, "*.gcda", start_path)
    if not gcno_files:
        sys.exit("No .gcno files found!")
    
    output_file = os.path.join(coverage_report_dir, "index.html")
    if use_wsl:
        args.insert(0, "wsl")
        output_file = abs_path_in_wsl(output_file)
    
    args = ["gcovr", "-r", start_path, "--html", "--html-details", "-o", output_file, "--txt-metric", "branch"]

    args = exclude_path(args, exclude_name)
    
    log(verbose, args)
    subprocess.run(args, check=True)


def generate_html_report(coverage_report_dir : str, coverage_report_name : str, exclude_name : str,
                         use_wsl = False, verbose = False):

    print(f"Generate html report")

    input_file = os.path.join(coverage_report_dir, coverage_report_name)
    output_dir = os.path.join(coverage_report_dir)
    args = ["genhtml", "--function-coverage", "--branch-coverage"]

    args = exclude_path(args, exclude_name)

    if use_wsl:
        args.insert(0, "wsl")
        input_file = abs_path_in_wsl(input_file)
        output_dir = abs_path_in_wsl(output_dir)

    args += [f"{input_file}", f"--output-directory={output_dir}"]

    log(verbose, args)
    subprocess.run(args, check=True)


def generate_coverage_md(start_path, coverage_report_dir) -> None:

    index_path = os.path.join(coverage_report_dir, "index.html")
    index_rel_path = os.path.relpath(index_path, os.path.join(start_path, "docs"))
    index_rel_path = Path(os.path.join("..", index_rel_path)).as_posix()

    report_date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    text = "# Code Coverage\n" \
    "\n" \
    f"[Code coverage report]({index_rel_path})\n" \
    "\n" \
    f"generated {report_date}\n"

    with open(Path(os.path.join("docs", "COVERAGE.md")), 'w') as md_file:
        md_file.write(text)


def get_user_args():

    default_c = Compiler.CLANG
    default_i = '.'
    default_o = os.path.join("docs", "coverage")
    default_e = ""
    default_n = "coverage.info"

    parser = argparse.ArgumentParser(prog="Coverage Report",
                                     description="Python script runs test application to generate code coverage " +
                                     "reports in html. Test applications needs to be compiled with coverage flags " + 
                                     f"and have '{FILENAME_FRAGMENT}' frase in name for automatic discovery. " +
                                     "Depending on used flags, report can contain code coverage of branches, "
                                     "functions and lines.")
    
    parser.add_argument("-c", dest="compiler", type=str,
                        help=f"Compilator used to generate code coverage data. " +
                        f"Supported options '{Compiler.CLANG}' and '{Compiler.GCC}'. " +
                        f"Default: '{default_c}'", default=default_c)
    parser.add_argument("-t", dest="tool", type=str,
                        help=f"Tool used to generate coverage reports. Clang always use '{Tool.LCOV}', " +
                        f"gcc can use '{Tool.GCOVR}' or '{Tool.LCOV}', " +
                        f"Default: '{Tool.LCOV}' for {Compiler.CLANG}, " +
                        f"'{Tool.GCOVR}' for {Compiler.GCC}", default="")
    parser.add_argument("-i", dest="root_dir", type=Path,
                        help=f"Root directory for test applications discovery and coverage report generation. " +
                        f"Default: current working directory", default=default_i)
    parser.add_argument("-o", dest="coverage_report_dir", type=str,
                        help=f"Folder name to store coverage data. " +
                        f"Default: '{default_o}' directory in script directory", default=default_o)
    parser.add_argument("-e", dest="exclude_name", type=str,
                        help=f"Directory name to exclude from coverage statistics. " +
                        f"Default: '{default_e}'. " + 
                        f"NOTE: 'lcov' excludes by pattern, 'gcovr' excludes by exact name", default=default_e)
    parser.add_argument("-n", dest="coverage_report_name", type=str,
                        help=f"File name for merged .lcov files: Default: {default_n}", default=default_n)
    parser.add_argument("-v", "--verbose",
                        help=f"Output additional informations to terminal", action="store_true")
    args = parser.parse_args()

    if not args.tool:
        if args.compiler == Compiler.CLANG:
            args.tool = Tool.LCOV
        if args.compiler == Compiler.GCC:
            args.tool = Tool.GCOVR

    log(args.verbose, args)

    if args.compiler.lower() != Compiler.CLANG and args.compiler.lower() != Compiler.GCC:
        sys.exit(f"Unsupported compiler {args.compiler}!")

    if args.tool.lower() != Tool.LCOV and args.tool.lower() != Tool.GCOVR:
        sys.exit(f"Unsupported tool {args.tool}!")

    args.root_dir = os.path.abspath(args.root_dir)
    args.coverage_report_dir = os.path.abspath(args.coverage_report_dir)

    if not os.path.exists(args.root_dir):
        sys.exit(f"Path {args.root_dir} is not available!")

    if not os.path.exists(args.coverage_report_dir):
        try:
            os.makedirs(args.coverage_report_dir, exist_ok=True)
        except OSError as error:
            sys.exit(f"Path {args.coverage_report_dir} does not exist and could not be created!")

    return args

def main():

    args = get_user_args()

    use_wsl = detect_tools(args.tool, args.verbose)
    test_apps = find_test_apps(args.root_dir, verbose=args.verbose)

    clean_artifacts()

    # generate .profraw for clang coverage and .gcno for gcc coverage
    run_test_apps(test_apps, args.compiler)

    if(args.tool == Tool.LCOV):
        if args.compiler == Compiler.CLANG:
            generate_profdata(start_path=args.root_dir, verbose=args.verbose)
            generate_lcov(test_apps, start_path=args.root_dir)

        generate_info(start_path=args.root_dir, compiler=args.compiler, coverage_report_dir=args.coverage_report_dir,
                      coverage_report_name=args.coverage_report_name, use_wsl=use_wsl, verbose=args.verbose)
        
        generate_html_report(coverage_report_dir=args.coverage_report_dir,
                             coverage_report_name=args.coverage_report_name,
                             exclude_name=args.exclude_name,
                             use_wsl=use_wsl, verbose=args.verbose)

    if(args.tool == Tool.GCOVR):
        if args.compiler == Compiler.GCC:
            generate_gcovr_report(start_path=args.root_dir, coverage_report_dir=args.coverage_report_dir,
                                  exclude_name=args.exclude_name,
                                  use_wsl=use_wsl, verbose=args.verbose)
        else:
            sys.exit(f"Unsupported combination of compiler {args.compiler} and coverage tool {args.tool}. Exiting!")

    generate_coverage_md(start_path=args.root_dir, coverage_report_dir=args.coverage_report_dir)

if __name__ == "__main__":
    main()

