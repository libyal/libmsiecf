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

  def test_get_type(self):
    """Tests the get_type function and type property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    msiecf_item = pymsiecf.item()

    msiecf_item.open(test_source)

    type = msiecf_item.get_type()
    self.assertIsNotNone(type)

    self.assertIsNotNone(msiecf_item.type)

    msiecf_item.close()

  def test_get_flags(self):
    """Tests the get_flags function and flags property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    msiecf_item = pymsiecf.item()

    msiecf_item.open(test_source)

    flags = msiecf_item.get_flags()
    self.assertIsNotNone(flags)

    self.assertIsNotNone(msiecf_item.flags)

    msiecf_item.close()

  def test_get_offset(self):
    """Tests the get_offset function."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    msiecf_item = pymsiecf.item()

    msiecf_item.open(test_source)

    offset = msiecf_item.get_offset()
    self.assertIsNotNone(offset)

    msiecf_item.close()


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()


  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])



  unittest.main(argv=unknown_options, verbosity=2)
