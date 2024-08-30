import unittest
import subprocess
import os


class TestTodoListTerminal(unittest.TestCase):

    def setUp(self):
        self.todo_list_executable = 'python3 main.py'
        self.solution_executable = 'python3 solution.py'
        self.filename = 'todo.csv'
        self.addCleanup(self.cleanup)

    def cleanup(self):
        if os.path.exists(self.filename):
            os.remove(self.filename)

    def run_command(self, executable, command):
        return subprocess.run(f'{executable} {command}', shell=True, capture_output=True, text=True)

    def test_create_task(self):
        result = self.run_command(self.todo_list_executable, 'create "Test Task 1"')
        self.assertEqual('Task "Test Task 1" created successfully.', result.stdout.strip())
        with open('todo.csv', 'r') as file:
            self.assertEqual('Test Task 1,Medium,0', file.readlines()[0].strip())

    def test_list_tasks(self):
        self.run_command(self.todo_list_executable, 'create "Test Task 1"')

        result = self.run_command(self.todo_list_executable, 'list')
        expected_output = '''Task List:
Index  Title           Priority   Done      
1      Test Task 1     Medium     0'''
        self.assertEqual(expected_output, result.stdout.strip())


    def setUp(self):
        self.todo_list_executable = 'python3 main.py'
        self.solution_executable = 'python3 solution.py'
        self.filename = 'todo.csv'
        self.addCleanup(self.cleanup)

    def cleanup(self):
        if os.path.exists(self.filename):
            os.remove(self.filename)

    def run_command(self, executable, command):
        return subprocess.run(f'{executable} {command}', shell=True, capture_output=True, text=True)

    def test_delete_task(self):
        self.run_command(self.todo_list_executable, 'create "Test Task 1"')
        self.run_command(self.todo_list_executable, 'create "Test Task 2"')

        result = self.run_command(self.todo_list_executable, 'delete "Test Task 1"')
        self.assertEqual('Task "Test Task 1" deleted successfully.', result.stdout.strip())
        with open('todo.csv', 'r') as file:
            self.assertEqual('Test Task 2,Medium,0', file.readlines()[0].strip())

    def test_clear_list(self):
        self.run_command(self.todo_list_executable, 'create "Test Task 1"')
        self.run_command(self.todo_list_executable, 'create "Test Task 2"')

        result = self.run_command(self.todo_list_executable, 'clear')
        self.assertEqual('To-do list cleared successfully.', result.stdout.strip())



if __name__ == '__main__':
    unittest.main()
