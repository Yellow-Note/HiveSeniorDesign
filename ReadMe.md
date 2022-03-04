# The Hive
## Autonomous UAV Search and Rescue Project

[The Spec. Doc](https://docs.google.com/document/d/1P7WHhIStPZlg40G0gDEU_NLqLtBaFG7JJOGIgDq67hg/edit)

## Current Tasks
| Name | Task | Selfmade deadline |
|---|---|---|
| Tim | Double checking math in the RXD algorithm | 2/17 |
| James L | Multithread RXD algorithm | Completed for currenmt build |
| James H | Working on the slicer, testing James L's code | TBD |
| Andrew | Working on GUI | Ongoing |
| Sam | Working on GUI | 2/20|



## Task List

- [ ] everyone brush up on C# and/or C++
- [ ] Flush out task list

[Learn C++](https://www.w3schools.com/cpp/default.asp)

[Learn C#](https://www.w3schools.com/cs/index.php)

### Front end Completed
- [X] create skeleton GUI (Tim Bourque)
- [ ] flush out the skeleton GUI
- [ ] send signals from GUI to back end
- [ ] add settings
- [ ] display video metadata in front end

### Back end Completed
- [ ] pass info from back end to GUI
- [X] convert RXD to C++
- [ ] convert KRXD to C++
- [X] fix only square images bug in backend
- [ ] add settings
- [ ] pull metadata from video file and give to front end
- [ ] work on Ground Sample Distance

### Future tasks to add/sort
- [ ] Additional GUI features to allow for easier user interaction
- [ ] Clearest frame selection
- [ ] Remote connection and “live” analysis
- [ ] Add identification of individual anomalies
- [ ] Making sure the software can work with more video/photo file formats, Convert video if possible
- [ ] Improvements to the speed of the algorithm(s); parallel operations
- [ ] Implementing additional algorithms; anomalous movement and KRXD
- [ ] Feature for multispectral imaging
- [ ] Bell curve selection of frame group
- [ ] Creating a program that installs and runs natively in Windows
- [ ] Check validity of video
- [ ] Setting: Algorithm
- [ ] Settings: Output location
- [ ] Settings: Grouping of frames and removing unnecessary frames
- [ ] Settings: Select enable or disable of parrellazation
- [ ] progress bar
- [ ] GIS with coordinates / timestamp
