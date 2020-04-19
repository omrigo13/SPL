import os
import sys

from DTO import Employee, Supplier, Product, Coffee_stand
from Repository import _Repository

def parse_file(config_file):
    try:
        repo = _Repository()
        repo.create_tables()
        config = open(config_file, "r")
        line = config.readline()
        while line != "":
            line = line.rstrip()
            line = line.split(",")
            if (line[0] == "E"):
                employee = Employee(line[1],line[2],line[3],line[4])
                employees = repo.employees
                employees.insert(employee)
            elif (line[0] == "S"):
                supplier = Supplier(line[1], line[2], line[3])
                suppliers = repo.suppliers
                suppliers.insert(supplier)
            elif (line[0] == "P"):
                product = Product(line[1], line[2], line[3], 0)
                products = repo.products
                products.insert(product)
            elif (line[0] == "C"):
                coffee_stand = Coffee_stand(line[1], line[2], line[3])
                coffee_stands = repo.coffee_stands
                coffee_stands.insert(coffee_stand)
            line = config.readline()
        repo._close()
        config.close()
    except IOError:
        print("Could not open file")

parse_file(sys.argv[1])
