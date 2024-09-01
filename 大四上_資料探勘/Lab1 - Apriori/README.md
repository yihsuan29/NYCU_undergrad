## STEPII
### Usage

To use the Apriori algorithm, navigate to the project directory ~/DM_HW1_109705001_陳以瑄/SourceCode and run the following command:

```bash
python StepII_apriori.py [-f file_path] [-s min_support] [-t task_id]
```

### Arguments
* -f file_path: Relative file path. The default value is none.
* -s min_support (optional): Minimum support ratio. Range is 0~1. The default value is 0.1.
* -t task_id (optional): Task identifier. Use 1 for task 1 and 2 for task 2. The default value is 1.

### Examples
Here are some example usages:

* Run the Apriori algorithm with a custom file path and minimum support:

```bash
python StepII_apriori.py -f ../Datasets/A.data -s 0.05 -t 1
```
* Run the Apriori algorithm for task 2 with default parameters:

```bash
python StepII_apriori.py -f ../Datasets/A.data -s 0.05 -t 2
```

## STEPIII
### Usage

To run the Eclat algorithm, navigate to the project directory ~/DM_HW1_109705001_陳以瑄/SourceCode and use the following command:

```bash
python StepIII_eclat.py [-f file_path] [-s min_support]
```

### Arguments
* -f file_path: Relative file path. The default value is none.
* -s min_support (optional): Minimum support ratio. Range is 0~1. The default value is 0.1.

### Example

* Run the Eclat algorithm with a custom file path and minimum support:

```bash
python StepIII_eclat.py -f ../Datasets/A.data -s 0.01
```