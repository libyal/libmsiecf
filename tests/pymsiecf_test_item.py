#!/usr/bin/env python
#
# Python-bindings item type test script
#
# Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import os
import sys
import unittest

import pymsiecf


class ItemTypeTests(unittest.TestCase):
  """Tests the item type."""

  def test_get_offset(self):
    """Tests the get_offset function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    msiecf_file = pymsiecf.file()

    msiecf_file.open(test_source)

    try:
      if not msiecf_file.number_of_items:
        raise unittest.SkipTest("missing items")

      msiecf_item = msiecf_file.get_item(0)

      offset = msiecf_item.get_offset()
      self.assertIsNotNone(offset)

    finally:
      msiecf_file.close()


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument(
      "source", nargs="?", action="store", metavar="PATH",
      default=None, help="path of the source file.")

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  setattr(unittest, "source", options.source)

  unittest.main(argv=unknown_options, verbosity=2)
