# Sudoku
## Summary
* A basic recreation of the clasic game Sudoku. When loaded it create a random 9 by 9 of numbers or blank spots. To play you enter the correct numbers in blank spots. Once you finished you can submit to check if everthng is correct.
* QT is used as the base widget engine. To create a Sudoku board with one answer the program uses recursive backtracking to create a finished Sudoku board. Then, it removes one random square and checks how many answers there are to the board. This repeats until there are two ansers to the board, where then it uses the previous checked board with one answer. Since we thenalready have the solution when the player is done playing we can just compare thier answer the answr we have.

## Controls
There are two control options.
* **Mouse**: By clicking an editable squar with your mouse a 3 by 3 will apear with all 9 choosable numbers. Once clicked the number will apear in the square.
* **Keyboard**: By selecting a editable sqare with your mouse you can then just enter a number on your keyboard or numbpad and it will apear in the square. 0 to delete the current number.
![2023-08-30-21-53-03](https://github.com/Arct1cPharaoh/Sudoku/assets/78323370/f59fffe5-a787-45bd-8962-6585e1e28828)
## Install
* Download the installer from GitHub release.
* Run Installer.
