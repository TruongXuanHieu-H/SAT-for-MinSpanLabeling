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

    # Highest label UNSAT
    unsat_labels = re.findall(
        r's \[Incremental\] UNSAT \(label = (\d+)\)\.',
        content
    )

    highest_unsat = unsat_labels[0] if unsat_labels else "-"

    # Lowest label SAT
    sat_side_labels = []

    for m in re.finditer(
        r's \[Incremental\] SAT \(label = (\d+)\)\.'
        r'|c \[Incremental\] Label (\d+) is removed from searching\.',
        content
    ):
        label = m.group(1) if m.group(1) is not None else m.group(2)
        sat_side_labels.append(label)

    lowest_sat = sat_side_labels[-1] if sat_side_labels else "-"

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

        "Highest label UNSAT": highest_unsat,

        "Lowest label SAT": lowest_sat,

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
                "Target value",
                "Lower bound",
                "Upper bound",
                "Highest label UNSAT",
                "Lowest label SAT",
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
        description="Parse incremental SAT logs into an Excel summary."
    )

    parser.add_argument(
        "root_dir",
        help="Root directory containing experiment folders"
    )

    parser.add_argument(
        "output_file",
        help="Output Excel file"
    )

    args = parser.parse_args()

    main(args.root_dir, args.output_file)