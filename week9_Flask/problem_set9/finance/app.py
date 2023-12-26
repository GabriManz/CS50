import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter definded in helpers.py
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Select user's stock portfolio and cash total
    rows = db.execute(
        """SELECT symbol, SUM(shares)
                      FROM portfolio
                      WHERE userid = ?
                      GROUP BY symbol
                      HAVING shares > 0""",
                      session["user_id"])

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    # Get cash value float for the userid
    cash = cash[0]['cash']
    user_total = cash

    # Add stock name, add current lookup value, add total value
    for row in rows:
        look = lookup(row['symbol'])
        row['name'] = look['name']
        row['price'] = look['price']
        row['total'] = row['price'] * row['shares']

        # Increment sum
        user_total = row['total'] + user_total

        # Convert price and total to usd format
        row['price'] = usd(row['price'])
        row['total'] = usd(row['total'])

    return render_template("index.html", rows=rows, cash=usd(cash), user_total=usd(user_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    #POST
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        quote = lookup(symbol)

        # Ensure sybol was submitted and exist
        if not symbol or quote is None:
            return apology("must provide a valid symbol", 400)

        # Ensure shares was submitted
        if not shares:
            return apology("must provide shares", 400)

        # Configuration of the values
        symbol = symbol.upper
        shares = int(shares)
        purchase = quote['price'] * shares

        # User cash balance
        balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        balance = balance[0]['cash']
        remain = balance - purchase
        if remain < 0:
            return apology("Not enough cash", 400)

        #Before this we add a new table (portfolio) in finance.db
        # Query database for username
        rows = db.execute("SELECT * FROM portfolio WHERE userid = ? AND symbol = ?", session["user_id"], symbol)

        # Ensure userid and symbol exist. If not exist, inser into portfolio
        if rows != 1:
            db.execute("INSERT INTO portfolio (userid, symbol) VALUES (?, ?)", session["user_id"], symbol)

        # Get previous number of shares owned
        oldshares = db.execute("SELECT shares FROM portfolio WHERE userid = ? AND symbol = ?", session["user_id"], symbol)
        oldshares = oldshares[0]["shares"]

        # Add purchased shares to previous share number
        newshares = oldshares + shares

        # Update shares in portfolio table
        db.execute("UPDATE portfolio SET shares = ? WHERE userid = ? AND symbol = ?",newshares, session["user_id"], symbol)

        # Update cash balance in users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, session["user_id"])

        #Create history Table
        # update history table
        db.execute("INSERT INTO history (userid, symbol, shares, method, price) VALUES (?, ?, ?, 'Buy', ?)", session["user_id"], symbol, shares, quote['price'])

        return redirect("/")

    #GET
    elif request.method == "GET":
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT * FROM history WHERE userid = ?", session["user_id"])

    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    #POST return quoted.html
    if request.method == "POST":
        #Lookup is implemented in helper.py
        symbol = lookup(request.form.get("symbol"))
        if symbol == None:
            return apology("Symbol not found", 400)

        return render_template("quoted.html", symbol=symbol)

    # GET return quote.html
    elif request.method == "GET":
        return render_template("quote.html")

def validate(password):
    import re
    if len(password) < 8:
        return apology("Password must be 8 characters or more", 400)

    # Check if the password has at least one letter
    if not re.search("[a-zA-Z]", password):
        return apology("Password must have 1 letter or more", 400)

    # Check if the password has at least one number
    if not re.search("[0-9]", password):
        return apology("Password must have 1 number or more", 400)

    # Check if the password has at least one special character
    if not re.search("[!@#$%^&*(),.?\":{}|<>]", password):
        return apology("Password must have 1 especial character or more", 400)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

     # User reached route via POST (submitting the register form)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        #Validate user's password
        validation = validate(request.form.get("password"))
        if validation == 0:
            return validation

        # Ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Save username and password hash in variables
        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))

        # Query database to ensure username isn't already taken
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) != 0:
            return apology("Username is already taken", 400)

        # Insert username and hash into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # Redirect to login page
        return redirect("/")

    # User reached route via GET
    elif request.method == "GET":
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    #POST
    if request.method == "POST":
        #Save element from form
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        quote = lookup(symbol)
        rows = db.execute("SELECT * FROM portfolio WHERE userid = ? AND symbol = ?", session['user_id'], symbol)

        # Ensure symbol exist
        if len(rows) != 1:
            return apology("must provide a valid symbol", 400)

        #Ensure shares was submitted
        if not shares:
            return apology("must submitted numer of shares", 400)

        # Check if the user is trying to sell more shares than they own
        old_shares = rows[0]['shares']
        if shares > old_shares:
            return apology("Can't sell more shares than you own")

        # Update cash value after sold
        sold = quote['price'] * shares
        cash = db.execute("SELECT cash FROM users WHERE ID = ?", session['user_id'])
        cash = cash[0]['cash']
        cash = cash + sold
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session['user_id'])

        #Update shares value after sold
        new_shares = old_shares - shares
        if new_shares > 0:
            db.execute("UPDATE users SET shares = ? WHERE id = ? AND symbol = ?", new_shares, session['user_id'], symbol)
        else:
            db.execute("DELETE FROM portfolio WHERE symbol = ? AND userid = ?", symbol, session['user_id'])

        #Update history table
        db.execute("""INSERT INTO history (userid, symbol, shares, method, price)
                   VALUES (?, ?, ?, ?, ?)""",
                   session['user_id'], symbol, new_shares, 'Sell', quote['price'])

        #Redirect to indexpage
        return redirect("/")

    #GET
    elif request.method == "GET":

        #Get user stock
        user_stock = db.execute("SELECT symbol FROM portfolio WHERE userid = ?", session["user_id"])

        #Return tu sell.html
        return render_template("sell.html", user_stock=user_stock)
