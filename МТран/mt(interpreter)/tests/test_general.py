import os
import sys
import unittest

sys.path.insert(0, '..')
from pycparser import parse_file, c_ast
from tests.test_util import cpp_supported, cpp_path, cpp_args

# Test successful parsing
#
class TestParsing(unittest.TestCase):
    def _find_file(self, name):
        """ Find a c file by name, taking into account the current dir can be
            in a couple of typical places
        """
        testdir = os.path.dirname(__file__)
        name = os.path.join(testdir, 'c_files', name)
        assert os.path.exists(name)
        return name

    def test_without_cpp(self):
        ast = parse_file(self._find_file('example_c_file.c'))
        self.assertIsInstance(ast, c_ast.FileAST)

    @unittest.skipUnless(cpp_supported(), 'cpp only works on Unix')
    def test_with_cpp(self):
        memmgr_path = self._find_file('memmgr.c')
        c_files_path = os.path.dirname(memmgr_path)
        ast = parse_file(memmgr_path, use_cpp=True,
            cpp_path=cpp_path(), cpp_args=cpp_args('-I%s' % c_files_path))
        self.assertIsInstance(ast, c_ast.FileAST)

        fake_libc = os.path.join(c_files_path, '..', '..',
                                 'utils', 'fake_libc_include')
        ast2 = parse_file(self._find_file('year.c'), use_cpp=True,
            cpp_path=cpp_path(), cpp_args=cpp_args('-I%s' % fake_libc))

        self.assertIsInstance(ast2, c_ast.FileAST)

    @unittest.skipUnless(cpp_supported(), 'cpp only works on Unix')
    def test_cpp_funkydir(self):
        # This test contains Windows specific path escapes
        if sys.platform != 'win32':
            return

        c_files_path = os.path.join('tests', 'c_files')
        ast = parse_file(self._find_file('simplemain.c'), use_cpp=True,
            cpp_path=cpp_path(), cpp_args=cpp_args('-I%s' % c_files_path))
        self.assertIsInstance(ast, c_ast.FileAST)

    @unittest.skipUnless(cpp_supported(), 'cpp only works on Unix')
    def test_no_real_content_after_cpp(self):
        ast = parse_file(self._find_file('empty.h'), use_cpp=True,
            cpp_path=cpp_path(), cpp_args=cpp_args())
        self.assertIsInstance(ast, c_ast.FileAST)

    @unittest.skipUnless(cpp_supported(), 'cpp only works on Unix')
    def test_c11_with_cpp(self):
        c_files_path = os.path.join('tests', 'c_files')
        fake_libc = os.path.join(c_files_path, '..', '..',
                                 'utils', 'fake_libc_include')
        ast = parse_file(self._find_file('c11.c'), use_cpp=True,
            cpp_path=cpp_path(), cpp_args=cpp_args('-I%s' % fake_libc))
        self.assertIsInstance(ast, c_ast.FileAST)

if __name__ == '__main__':
    unittest.main()
