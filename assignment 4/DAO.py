class _Employees:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, Employee):
        values_to_add = "INSERT INTO Employees (id, name, salary, coffee_stand) VALUES (?,?,?,?)"
        self._conn.execute(values_to_add, (Employee.id, Employee.name, Employee.salary, Employee.coffee_stand))

    def print_a_list(self):
        employees_table = "SELECT * FROM Employees ORDER BY id"
        employees_table = self._conn.execute(employees_table)
        employees_table = employees_table.fetchall()
        for employee in employees_table:
            print(employee)

class _Suppliers:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, Supplier):
        values_to_add = "INSERT INTO Suppliers (id, name, contact_information) VALUES (?,?,?)"
        self._conn.execute(values_to_add, (Supplier.id, Supplier.name, Supplier.contact_information))

    def print_a_list(self):
        suppliers_table = "SELECT * FROM Suppliers ORDER BY id"
        suppliers_table = self._conn.execute(suppliers_table)
        suppliers_table = suppliers_table.fetchall()
        for supplier in suppliers_table:
            print(supplier)

class _Products:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, Product):
        values_to_add = "INSERT INTO Products (id, description, price, quantity) VALUES (?,?,?,?)"
        self._conn.execute(values_to_add, (Product.id, Product.description, Product.price, Product.quantity))

    def print_a_list(self):
        products_table = "SELECT * FROM Products ORDER BY id"
        products_table = self._conn.execute(products_table)
        products_table = products_table.fetchall()
        for product in products_table:
            print(product)

    def update(self, quantity, id):
        update_query = "UPDATE Products SET quantity = quantity + ? WHERE id = ?"
        self._conn.execute(update_query, (quantity, id))

class _Coffee_stands:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, Coffee_stand):
        values_to_add = "INSERT INTO Coffee_stands (id, location, number_of_employees) VALUES (?,?,?)"
        self._conn.execute(values_to_add, (Coffee_stand.id, Coffee_stand.location, Coffee_stand.number_of_employees))

    def print_a_list(self):
        coffee_stands_table = "SELECT * FROM Coffee_stands ORDER BY id"
        coffee_stands_table = self._conn.execute(coffee_stands_table)
        coffee_stands_table = coffee_stands_table.fetchall()
        for coffee_stand in coffee_stands_table:
            print(coffee_stand)

class _Activities:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, activity):
        values_to_add = "INSERT INTO Activities (product_id, quantity, activator_id, date) VALUES (?,?,?,?)"
        self._conn.execute(values_to_add, (activity.product_id, activity.quantity, activity.activator_id, activity.date))

    def check_amount(self, activity):
        query = "SELECT SUM(quantity) as amount FROM Activities WHERE product_id = ?"
        current_product_quantity = self._conn.execute(query,(activity.product_id,))
        current_product_quantity = current_product_quantity.fetchone()[0]
        total = int(activity.quantity) + current_product_quantity
        return total,current_product_quantity

    def print_a_list(self):
        activities_table = "SELECT * FROM Activities ORDER BY date"
        activities_table = self._conn.execute(activities_table)
        activities_table = activities_table.fetchall()
        for activity in activities_table:
            print(activity)


