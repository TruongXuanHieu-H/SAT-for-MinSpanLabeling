import os
import re
import argparse
import pandas as pd


def extract(pattern, text, default=""):
    m = re.search(pattern, text, re.MULTILINE)
    return m.group(1).strip() if m else default


def parse_log(filepath):
    with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
        content = f.read()

    row = {
        "File": os.path.basename(filepath),

        "Problem": extract(
            r'c \[Main\] Encoding and solving for graph:\s*(.*?)\.',
            content
        ),

        "Memory limit (MB)": extract(
            r'c \[Param\] Memory limit is set to\s+(\d+)',
            content
        ),

        "Real time limit (s)": extract(
            r'c \[Param\] Real time limit is set to\s+(\d+)',
            content
        ),

        "Worker count": extract(
            r'c \[Param\] Worker count is set to\s+(\d+)',
            content
        ),

        "Target value": extract(
            r'c \[Incremental\] Encoding starts with target value = (\d+):',
            content
        ),

        "Lower bound": extract(
            r'c \[Param\] LB is predefined as\s+(\d+)',
            content
        ),

        "Upper bound": extract(
            r'c \[Param\] UB is predefined as\s+(\d+)',
            content
        ),

        "Highest label UNSAT": extract(
            r'r \[Main\] Highest label UNSAT:\s*(-|\d+)\.?',
            content
        ),

        "Lowest label SAT": extract(
            r'r \[Main\] Lowest label SAT:\s*(-|\d+)\.?',
            content
        ),

        "Best span": (
            int(extract(
                r'r \[Main\] Lowest label SAT:\s*(-|\d+)\.?',
                content
            )) - 1
            if extract(
                r'r \[Main\] Lowest label SAT:\s*(-|\d+)\.?',
                content
            ) != "-"
            else "-"
        ),

        "Memory consumed (MB)": extract(
            r'r \[Main\] Total memory consumed:\s*([^\n\r]+) MB\.',
            content
        ),

        "Time consumed (ms)": extract(
            r'r \[Main\] Total real time:\s*([^\n\r]+) ms\.',
            content
        ),

        "Optimal found": "x"
    }

    if "c [Main] Lim pid ends with result:" in content:
        row["Optimal found"] = ""

    return row


def main(root_dir, output_file):
    with pd.ExcelWriter(
        output_file,
        engine="openpyxl"
    ) as writer:

        for folder in sorted(os.listdir(root_dir)):
            folder_path = os.path.join(root_dir, folder)

            if not os.path.isdir(folder_path):
                continue

            rows = []

            for filename in sorted(os.listdir(folder_path)):
                if not filename.endswith(".txt"):
                    continue

                filepath = os.path.join(folder_path, filename)

                try:
                    rows.append(parse_log(filepath))
                except Exception as e:
                    print(f"Error parsing {filepath}: {e}")

            if not rows:
                continue

            df = pd.DataFrame(rows)

            columns = [
                "File",
                "Problem",
                "Memory limit (MB)",
                "Real time limit (s)",
                "Worker count",
                "Target value",
                "Lower bound",
                "Upper bound",
                "Highest label UNSAT",
                "Lowest label SAT",
                "Best span",
                "Memory consumed (MB)",
                "Time consumed (ms)",
                "Optimal found"
            ]

            df = df[columns]

            sheet_name = folder[:31]

            df.to_excel(
                writer,
                sheet_name=sheet_name,
                index=False
            )

    print(f"Saved to {output_file}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Parse SAT iteration logs into an Excel summary."
    )

    parser.add_argument(
        "root_dir",
        nargs="?",
        default="./iteration",
        help="Root directory containing experiment folders"
    )

    parser.add_argument(
        "output_file",
        nargs="?",
        default="sat-iteration_summary.xlsx",
        help="Output Excel file"
    )

    args = parser.parse_args()

    main(args.root_dir, args.output_file)