import csv

def csv_to_txt(input_text, output_txt):
    # Read the text file (which has CSV format)
    with open(input_text, 'r') as txt_file:
        reader = csv.reader(txt_file)
        values = next(reader)  # Since there's only one row, we can directly read it

    # Convert non-zero values to 1
    values = [str(1 if int(cell) != 0 else 0) for cell in values]

    # Reshape the single row into 64x64 format
    rows = [values[i:i+64] for i in range(0, 4096, 64)]

    # Write to the output text file
    with open(output_txt, 'w') as out_file:
        out_file.write('w:64\n')
        out_file.write('h:64\n')
        for row in rows:
            out_file.write(','.join(row) + '\n')  # This will automatically not have a comma after the last value

if __name__ == "__main__":
    # Example usage
    input_text_path = input("Enter the path to the text file with 4096 CSV values: ")
    output_txt_name = input("Enter the desired name for the output text file: ")
    csv_to_txt(input_text_path, output_txt_name)
