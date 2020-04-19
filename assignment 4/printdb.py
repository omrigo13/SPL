from Repository import _Repository


def printdb():
    repo = _Repository()
    print("Activities")
    repo.activities.print_a_list()
    print("Coffee stands")
    repo.coffee_stands.print_a_list()
    print("Employees")
    repo.employees.print_a_list()
    print("Products")
    repo.products.print_a_list()
    print("Suppliers")
    repo.suppliers.print_a_list()
    print("\nEmployees report")
    repo.employees_report()
    report_data = repo.activities_report()
    if(report_data != 0):
        print("\nActivities")
        for activity in report_data: print(activity)


def main():
    printdb()

if __name__ == '__main__':
    main()