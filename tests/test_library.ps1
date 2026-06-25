# Tests library functions and types.

$LibraryTests = "allocation_table cache_directory_table directory_descriptor error file_header hash_table io_handle item item_descriptor leak_values notify property_type redirected_values url_values"
$LibraryTestsWithInput = "file support"
$OptionSets = "" -split " "

. .\test_functions.ps1

$TestExecutablesDirectory = GetTestExecutablesDirectory

If (-Not (Test-Path ${TestExecutablesDirectory}))
{
	Write-Error "Missing test executables directory"

	Exit ${ExitFailure}
}

$Result = ${ExitSuccess}

Foreach (${TestName} in ${LibraryTests} -split " ")
{
	# Split will return an array of a single empty string when LibraryTests is empty.
	If (-Not (${TestName}))
	{
		Continue
	}
	$ResultRun = RunTestBinary ${TestExecutablesDirectory} "msiecf_test_${TestName}"

	If ((${ResultRun} -ne ${ExitSuccess}) -And (${ResultRun} -ne ${ExitIgnore}))
	{
		$Result = ${ResultRun}
	}
}

$TestInputs = GenerateTestInputs "libmsiecf" ${OptionSets}

Foreach (${TestName} in ${LibraryTestsWithInput} -split " ")
{
	# Split will return an array of a single empty string when LibraryTestsWithInput is empty.
	If (-Not (${TestName}))
	{
		Continue
	}
	ForEach ($TestInput in ${TestInputs})
	{
		$ResultRun = RunTestBinaryWithInput ${TestExecutablesDirectory} "msiecf_test_${TestName}" ${TestInput}

		If ((${ResultRun} -ne ${ExitSuccess}) -And (${ResultRun} -ne ${ExitIgnore}))
		{
			$Result = ${ResultRun}
		}
	}
}

Exit ${Result}
