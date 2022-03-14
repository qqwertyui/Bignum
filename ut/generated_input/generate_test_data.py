import argparse
import random
import math
import json

MIN_ELEMENT_SIZE = -1000000000000000000000000000000
MAX_ELEMENT_SIZE = 10000000000000000000000000000000

class Test:
  def __init__(self, action, number_of_args):
    self.action = action
    self.number_of_args = number_of_args

def add(a,b):
  return a+b
def sub(a,b):
  return a-b
def mul(a,b):
  return a*b
def div(a,b):
  return int(a/b)
def mod(a,b):
  return a%b
def pow(a,b):
  return a**b
def sqrt(a):
  return math.sqrt(a)

TEST_TYPES = {
  "add" : Test(add, 2),
  "sub" : Test(sub, 2),
  "mul" : Test(mul, 2),
  "div" : Test(div, 2),
  "mod" : Test(mod, 2),
}

def parse_arguments():
  parser = argparse.ArgumentParser()
  parser.add_argument("test_name")
  parser.add_argument("number_of_tests", type=int)
  return vars(parser.parse_args())

def generate_numbers(n, min, max):
  return [random.randint(min, max) for i in range(n)]

def generate_tests(test, number_of_tests):
  result_json = "{\"testcases\":["
  for i in range(number_of_tests):
    generated_input = generate_numbers(test.number_of_args, MIN_ELEMENT_SIZE, MAX_ELEMENT_SIZE)
    expected_output = test.action(*generated_input)
    generated_input_string = [str(i) for i in generated_input]
    expected_output_string = str(expected_output)
    result_json += json.JSONEncoder().encode({"input":generated_input_string, "output":expected_output_string})
    if(i != (number_of_tests-1)):
      result_json += ","
  result_json += "]}"
  return result_json

def save_test_data(filename, data):
  with open(filename + ".json", "w") as output_file:
    output_file.write(data)

def main():
  args = parse_arguments()
  tests = generate_tests(TEST_TYPES[args["test_name"]], args["number_of_tests"])
  save_test_data(args["test_name"], tests)

if __name__ == "__main__":
  main()