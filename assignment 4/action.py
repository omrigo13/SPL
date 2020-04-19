import os
import sys

from DTO import Activitiy
from Repository import _Repository
from printdb import printdb


def parse_file(config_file):
    try:
        repo = _Repository()
        config = open(config_file, "r")
        line = config.readline()
        while line != "":
            line = line.rstrip()
            line = line.split(",")
            activity = Activitiy(line[0].rstrip(), line[1], line[2], line[3])
            activities = repo.activities
            products = repo.products
            if (activity.quantity == 0):
                continue
            elif (activity.quantity > 0):
                activities.insert(activity)
                products.update(activity.quantity,activity.product_id)
            elif (activity.quantity < 0):
                if(activities.check_amount(activity)[0] >= 0 and activities.check_amount(activity)[1] >= 0):
                    activities.insert(activity)
                    products.update(activity.quantity, activity.product_id)
            line = config.readline()
        repo._close()
        config.close()
        printdb()
    except IOError:
        print("Could not open file")


parse_file(sys.argv[1])

