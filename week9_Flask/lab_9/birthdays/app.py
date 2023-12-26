import os
from cs50 import SQL
from flask import Flask, render_template, request, redirect

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # Add the user's entry into the database
        # Access form data
        message = ""
        name = request.form.get("name")
        day = request.form.get("day")
        month = request.form.get("month")

        if not name:
            message = "Missing name"
        elif not month:
            message = "Missing month"
        elif not day:
            message = "Missing day"
        else:
            db.execute("INSERT INTO birthdays (name, day, month) VALUES(?, ?, ?)", name, day, month)

        # Go back to homepage
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", message=message, birthdays=birthdays)

    else:
        # Display the entries in the database on index.html
        # Query for all birthdays
        birthdays = db.execute("SELECT * FROM birthdays")
        # Render birthdays page
        return render_template("index.html", birthdays=birthdays)

# Delete Route
@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")

if __name__ == "__main__":
    app.run(debug=True)
