#!/bin/sh
# Script that synchronizes the local test data
#
# Version: 20251217

REPOSITORY="dfirlabs/greendale-specimens";
TEST_DATA_PATH="msiecf/student-pc1/History.IE5";
TEST_SET="public";
TEST_INPUT_DIRECTORY="tests/input";
TEST_FILES="index.dat";

mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}";

for TEST_FILE in ${TEST_FILES};
do
	URL="https://raw.githubusercontent.com/${REPOSITORY}/refs/heads/main/${TEST_DATA_PATH}/${TEST_FILE}";

	curl -L -o "${TEST_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL};
done

