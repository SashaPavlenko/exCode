import csv
import os


def is_num(s: str):
    if len(s) != 0 and (s[0]):
        if s[0] == '-':
            s = s[1:]
        if len(s) != 0:
            point_count = s.count('.')
            if point_count > 1:
                return False
            elif point_count == 1:
                s1, s2 = s[:s.find('.')], s[s.find('.') + 1:]
                return s1.isdigit() and s2.isdigit()
            else:
                return s.isdigit()
        else:
            return False
    else:
        return False


class CarBase:
    def __init__(self, brand, photo_file_name, carrying):
        self.brand = brand
        self.photo_file_name = photo_file_name
        self.carrying = float(carrying)

    # @staticmethod
    def get_photo_file_ext(self):
        return os.path.splitext(self.photo_file_name)[1]


class Car(CarBase):
    def __init__(self, brand, photo_file_name, carrying, passenger_seats_count):
        super().__init__(brand, photo_file_name, carrying)
        self.passenger_seats_count = int(passenger_seats_count)

    car_type = 'car'


class Truck(CarBase):
    def __init__(self, brand, photo_file_name, carrying, body_whl):
        super().__init__(brand, photo_file_name, carrying)

        self.body_whl = body_whl

        body_whl_list = body_whl.split('x')

        if len(body_whl_list) == 3:
            try:
                self.body_length = float(body_whl_list[0])
            except Exception:
                self.body_length = 0.0

            try:
                self.body_width = float(body_whl_list[1])
            except Exception:
                self.body_width = 0.0

            try:
                self.body_height = float(body_whl_list[2])
            except Exception:
                self.body_height = 0.0
        else:
            self.body_width = 0.0
            self.body_height = 0.0
            self.body_length = 0.0

    def get_body_volume(self):
        return self.body_width * self.body_length * self.body_height

    car_type = 'truck'

class SpecMachine(CarBase):
    def __init__(self, brand, photo_file_name, carrying, extra):
        super().__init__(brand, photo_file_name, carrying)
        self.extra = extra

    car_type = 'spec_machine'


def get_car_list(csv_filename):
    """
    Get file of csv extension.
    Return contained list from file where orther rows is list of object property:
    0 - Тип (car_type)
    1 - Марка (brand)
    2 - Кол-во пассажирских мест (passenger_seats_count)
    3 - Фото (photo_file_name)
    4 - Кузов ДxШxВ, м (body_whl)
    5 - Грузоподъемность, Тонн (carrying)
    6 - Дополнительно (extra)

    """

    car_list = []
    with open(csv_filename, encoding='utf-8') as csv_fd:
        reader = csv.reader(csv_fd, delimiter=';')
        next(reader)
        for row in reader:

            if len(row) == 7 and row[0] in ('car', 'truck', 'spec_machine') \
                        and row[1] != '' \
                        and len(row[5]) != '' and is_num(row[5]) and float(row[5]) >= 0 \
                        and row[3] != '' \
                        and os.path.splitext(row[3])[1] in ('.jpg', '.jpeg', '.png', '.gif'):

                # If row doesn't have column which mustn't be in this row, then this row is valid and
                # we will append it to car_list.
                if row[0] == 'car' and row[2] != '':
                    if row[4] == '' and row[6] == '':
                        car_list.append(Car(row[1], row[3], row[5], row[2]))

                elif row[0] == 'truck':
                    if row[2] == '' and row[6] == '':

                        body_whl = row[4]
                        body_whl= body_whl.split('x')
                        if not(len(body_whl) == 3 and len(list(filter(is_num, body_whl))) == 3):
                            row[4] = '0x0x0'
                        car_list.append(Truck(row[1], row[3], row[5], row[4]))

                elif row[0] == 'spec_machine' and row[6] != '':
                    if not (row[2] and row[4]):
                        car_list.append(SpecMachine(row[1], row[3], row[5], row[6]))

    return car_list


def get_car_list_their(csv_filename):

    car_types = {'car': Car, 'spec_machine': SpecMachine, 'truck': Truck}
    csv.register_dialect('cars', delimiter=';')
    car_list = []

    with open(csv_filename, 'r') as file:
        reader = csv.DictReader(file, dialect='cars')
        for row in reader:
            try:
                car_class = car_types[row['car_type']]
                car_list.append(car_class.create_from_dict(row))
            except Exception:
                pass

    return car_list

a = get_car_list_their('test.csv')
