# 3081 Lab 4: Code Styling
_(Due: Thursday, October. 6, 2022 @ 11:59pm)_

## General Information

### Accesing a Lab Machine

For this assignment, we suggest you use a lab machine in ***Keller Hall 1-250*** or ***Keller Hall 1-262*** ([details](https://cse.umn.edu/cseit/classrooms-labs#cselabs)). You can access a lab machine also remotely using [VOLE](https://github.umn.edu/umn-csci-3081-F22/shared-upstream/tree/main/FAQs/VOLE) and [SSH](https://github.umn.edu/umn-csci-3081-F22/shared-upstream/tree/main/FAQs/SSH).

**IMPORTANT: Inside the lab machine, only files saved to your home folder (e.g., `/home/kaung006`) will be persisted across sessions. If you log out, make sure your progress is pushed to GitHub or saved in the home folder.**

### Diskquota Exceed
One of the reasons you might not be able to log into a lab machine is that you reached your CSE Labs Account disk quota. <br>
To free up space, [see here](https://github.umn.edu/umn-csci-3081-F22/shared-upstream/tree/main/FAQs/CSE%20Disk%20Quota%20Exceeds)


## Retrieve Class Materials

1. Clone **public lab04** repo
    ```bash
    git clone git@github.umn.edu:umn-csci-3081-F22/public-lab04.git
    ```

2. Clone your **private lab04** repo<br>
    *Note: **replace** x500 with your x500*
    ```bash
    git clone git@github.umn.edu:umn-csci-3081-F22/x500-lab04
    ```

3. Copy the content of **public lab04** repo into your **private lab04** repo and you can start working inside your private repo.

## Lab Instructions

You will be refactoring some of the codes inside libs/routing/src folder to match the Google code style while maintaining the project structure.

### How to make sure your code style matches the Google style?
We will be using **cpplint** program as this program follows the Google code styling guideline which is perfect for us.
1. Before everything, try to run the program and see whether it worked or not.

    Inside the lib/ and src/ there are codes which takes in .osm file type and produce the shortest path from one point to another using 3 different algorithms (A*, Dijkstra and Depth First Search). This will be used in later labs to determine the path to choose. 

    1. To run the program, first locate to the your repo and go into the src folder
    2. Run `make` to build the applications
        ```
        make
        ```
    3. Note it builds all the applications. Let's execute them:<br>
    Usage: ./pathFinding_app [input graph] [output pic name]
        ```
        ./pathFinding_app ../lib/routing/data/umn.osm umn.png
        ```
        You can find the input graphs inside lib/routing/data
    4. Checkout the output path picture inside the src folder.  You should probably see something like this depending on the input file:
    <p align="center"><img src="pics/example_output.png" alt="path" width="80%"></p>

    - Green line  : A* algorithm (fastest route from Top Left to Bottom Right)
    - Orange line : Dijkstra algorithm (fastest route from Middle left to Middle Right)
    - Red line    : Depth First Search algorithm (a route from Top left to Bottom Right)

2. If it is showing error then let one of the TAs know about this.
3. Before proceeding, make sure you are in top folder and not inside the src folder.<br>
Run cpplint onto one of the src files
    ````bash
    cpplint --filter=-legal/copyright,-build/include,-build/namespaces,-runtime/explicit ./lib/routing/src/graph.cc
    ````
    *The filter keyword is to filter the errors that we do not want, which in our case, we want to exclude 4 cases (legal/copyright, build/include, build/namespaces, runtime/explicit).*<br>

    You will see something like
    ````bash
    ./lib/routing/src/graph.cc:10:  Line ends in whitespace.  Consider deleting these extra spaces.  [whitespace/end_of_line] [4]
    ./lib/routing/src/graph.cc:17:  An else should appear on the same line as the preceding }  [whitespace/newline] [4]
    .
    .
    .
    ./lib/routing/src/graph.cc:65:  Namespace should be terminated with "// namespace routing"  [readability/namespace] [5]
    Done processing ./lib/routing/src/graph.cc
    Total errors found: 9
    ````
    This means that there are 9 total errors that doesn't match the Google styling guide inside the graph.cc. 
4. Go into the `graph.cc` file and try to fix the errors manually by reading the errors output.
5. Check again using the cpplint to see whether the errors are still there or not using the command below. 
    ````bash
    cpplint --filter=-legal/copyright,-build/include,-build/namespaces,-runtime/explicit ./lib/routing/src/graph.cc
    ````
6. Manually checking and trying to fix the errors to match the styling guideline is very tedious. VS Code has a plugin to do this work automatically, but the computers in the lab do not properly support this plugin. If you want, you can try to use the VSCode linting/formatting extension (see the section below Final Submission), but we will have you manually fix 3 files in total:
    * lib/routing/src/graph.cc
    * lib/routing/src/parsers/osm/osm_parser.cc
    * lib/routing/src/routing/pathing.cc
    
    To see what needs to be fixed for each of the files, run the command in step 5 but replace the file path with your desired file.
    
    You can look at [Google's C++ Styleguide here](https://google.github.io/styleguide/cppguide.html) to help you fix the errors.
7. Once you have fixed the style issues for all three files, make sure your program still works (follow step 1 to re-make and run the program).
8. Push your refactored code to GitHub.

### Final Submission

To submit your assignment, post on the Gradescope assignment "Lab 4: Code Styling" your x500 and the commit ID for your submission.<br>
[Click here](https://github.umn.edu/umn-csci-3081-F22/shared-upstream/tree/main/FAQs/Commit%20ID) to see how to obtain commit ID.


### VS Code Linting Plugin

You can try to use the VS Code Linting pluging to automatically reformat files, but this isn't working for all students.

1. Press the extension icon <img src="pics/extensionIcon.png" width="20px"> on the left side OR press Ctrl + Shift + X
2. Search **C/C++** in the search bar
3. Then click on the first choice (C/C++, not C/C++ Extension Pack)
4. Press install
5. Go to the setting under File tab -> Preference -> Setting
6. Search "C_Cpp: Clang_format_fallback Style"
7. You will see something like the pic below
<p align="center"><img src="pics/settingC_CPP.png" width="800px"><p>

8. Change the "Visual Studio" into "Google"
9. Open the file that you would like to change the code style inside the visual studio by clicking the file icon <img src="pics/fileIcon.png" width="20px"> and selecting the file to open
10. Now is time to do apply the styling automatically. Press "Ctrl + Shift + P" and find **"format document"** then press ENTER OR press "Ctrl + Shift + I" as shortcut key. This will automatically format your codes into the styling that we specify (Google style guideline)
11. Note that this will **not fix** all the guideline that is needed, however this will reduce it tremendously
12. Check again using the cpplint on the graph.cc file and see whether it reduces the errors or not
