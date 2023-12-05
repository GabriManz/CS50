from sys import argv, exit
from cs50 import SQL
from csv import DictReader

# Check for correct usage command
while True:
    if len(argv) != 2:
        print('Usage: python import.py students.csv')
        exit(1)
    else:
        break

# Connect to the database
db = SQL('sqlite:///roster.db')

# Create tables
db.execute('''
CREATE TABLE IF NOT EXISTS students (
    id INTEGER PRIMARY KEY,
    student_name TEXT,
    house_id INTEGER,
    FOREIGN KEY (house_id) REFERENCES houses(id)
);
''')

db.execute('''
CREATE TABLE IF NOT EXISTS houses (
    id INTEGER PRIMARY KEY,
    house_name TEXT
);
''')

db.execute('''
CREATE TABLE IF NOT EXISTS assignments (
    student_id INTEGER,
    house_id INTEGER,
    PRIMARY KEY (student_id, house_id),
    FOREIGN KEY (student_id) REFERENCES students(id),
    FOREIGN KEY (house_id) REFERENCES houses(id)
);
''')

# Open csv file
csv_file = argv[1]
with open(f'{csv_file}', 'r') as students:
    # Create a CSV reader
    reader = DictReader(students)

    # Iterate over each row in the CSV file
    for row in reader:
        # Insert data into the 'houses' table in the database
        house_id = db.execute('INSERT OR IGNORE INTO houses (house_name) VALUES (?)',
                              row['house'])

        # Retrieve the last inserted row's ID
        house_id = db.execute('SELECT id FROM houses WHERE house_name = ?', row['house'])[0]['id']

        # Insert data into the 'assignments' table
        db.execute('INSERT INTO assignments (student_name, house_id) VALUES (?, ?)',
                   row['student_name'], house_id)

# Exit the program with status code 0 (success)
exit(0)
