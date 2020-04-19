import atexit
import os
import sqlite3

from DAO import _Employees, _Suppliers, _Coffee_stands, _Products, _Activities


class _Repository:
    def __init__(self):
        self._conn = sqlite3.connect('moncafe.db')
        self.employees = _Employees(self._conn)
        self.suppliers = _Suppliers(self._conn)
        self.products = _Products(self._conn)
        self.coffee_stands = _Coffee_stands(self._conn)
        self.activities = _Activities(self._conn)

    def _close(self):
        self._conn.commit()
        self._conn.close()

    def create_tables(self):

         self._conn.executescript(
                                 "DROP TABLE if EXISTS Employees; DROP TABLE if EXISTS Suppliers; DROP TABLE if EXISTS Products;"
                                 "DROP TABLE if EXISTS Coffee_stands; DROP TABLE if EXISTS Activities;"
                                 "CREATE TABLE Employees (id INTEGER PRIMARY KEY,name TEXT NOT NULL,salary REAL NOT NULL,coffee_stand INTEGER REFERENCES Coffee_stands(id));"
                                 "CREATE TABLE Suppliers (id INTEGER PRIMARY KEY, name TEXT NOT NULL, contact_information TEXT);"
                                 "CREATE TABLE Products (id INTEGER PRIMARY KEY, description TEXT NOT NULL, price REAL NOT NULL, quantity INTEGER NOT NULL);"
                                 "CREATE TABLE Coffee_stands (id INTEGER PRIMARY KEY, location TEXT NOT NULL, number_of_employees INTEGER);"
                                 "CREATE TABLE Activities (product_id INTEGER REFERENCES Products(id), quantity INTEGER NOT NULL, activator_id INTEGER NOT NULL, date DATE NOT NULL)")

    def employees_report(self):
        query = "SELECT DISTINCT q1.name, q1.salary, q1.location, q2.sum FROM" \
                "(SELECT name, salary, location FROM Employees, Coffee_stands, Products" \
                " WHERE Employees.coffee_stand = Coffee_stands.id GROUP BY Employees.id ORDER BY name) as q1 " \
                " LEFT JOIN  (SELECT name, salary, location, sum(-1*Activities.quantity*Products.price) as sum" \
                " FROM Employees, Coffee_stands, Products, Activities WHERE Employees.coffee_stand = Coffee_stands.id " \
                " AND Activities.product_id = Products.id AND Employees.id = Activities.activator_id GROUP BY Employees.id " \
                " ORDER BY name) as q2 ON q1.name = q2.name"
        query = self._conn.execute(query)
        query = query.fetchall()
        for line in query:
            line = list(line)
            if(line[3] == None):
                line[3] = 0
            print(str(line[0]) + " " + str(line[1]) + " " + str(line[2]) + " " + str(line[3]))

    def activities_report(self):
        query = "SELECT DISTINCT date, description, Activities.quantity, Employees.Name = 'None', Suppliers.name, Activities.ROWID FROM Activities, Products, Suppliers, Employees" \
                " WHERE Suppliers.id = Activities.activator_id AND Products.id = Activities.product_id" \
                " UNION " \
                "SELECT DISTINCT date, description, Activities.quantity, Employees.name, Suppliers.name = 'None', Activities.ROWID FROM Activities, Products, Employees, Suppliers" \
                " WHERE Employees.id = Activities.activator_id AND Products.id = Activities.product_id ORDER BY date, Activities.rowid"
        query = self._conn.execute(query)
        query = query.fetchall()
        if(query == []):
            return 0
        output = []
        for line in query:
            line = list(line)
            if(line[3] == 0):
                line[3] = None
            if(line[4] == 0):
                line[4] = None
            del line[-1]
            line = tuple(line)
            output.append(line)
        return output

repo = _Repository()
atexit.register(repo._close)