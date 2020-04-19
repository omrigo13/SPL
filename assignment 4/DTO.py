class Employee:
    def __init__(self, id, name, salary, coffee_stand):
        self.id = id
        self.name = name.strip()
        self.salary = salary
        self.coffee_stand = coffee_stand

    def __str__(self):
        return "(" + str(self.id) + ", " + str(self.name) + ", " + str(self.salary) + ", " \
        + str(self.coffee_stand) + ")"

class Supplier:
    def __init__(self, id, name, contact_information):
        self.id = id.strip()
        self.name = name.strip()
        self.contact_information = contact_information.strip()

    def __str__(self):
        return "(" + str(self.id) + ", " + str(self.name) + ", " + str(self.contact_information) + ")"

class Product:
    def __init__(self, id, description, price, quantity):
        self.id = id
        self.description = description.strip()
        self.price = price
        self.quantity = int(quantity)

    def __str__(self):
        return "(" + str(self.id) + ", " + str(self.description) + ", " + str(self.price) + ", " \
        + str(self.quantity) + ")"

class Coffee_stand:
    def __init__(self, id, location, number_of_employees):
        self.id = id
        self.location = location.strip()
        self.number_of_employees = number_of_employees

    def __str__(self):
        return "(" + str(self.id) + ", " + str(self.location) + ", " + str(self.number_of_employees) + ")"

class Activitiy:
    def __init__(self, product_id, quantity, activator_id, date):
        self.product_id = product_id
        self.quantity = int(quantity)
        self.activator_id = activator_id
        self.date = date

    def __str__(self):
        return "(" + str(self.product_id) + ", " + str(self.quantity) + ", " + str(self.activator_id) + ", " \
        + str(self.date) +")"