import csv
import os

def split(filename):
    matrix = []

    with open(filename) as source:
        with open('features.csv', 'w') as features:
            with open('label.csv', 'w') as labels:
                csv_reader = csv.reader(source, delimiter=',')
                line_count = 0
                for row in csv_reader:
                    features.write("{}\n".format(",".join(row[:-1])))
                    labels.write("{},".format(row[-1]))
split('./logistic-regression-vector/heart.csv')