Contains the BUR Unity Sim for the 2024 - 2025 season

The Sim file should contain
- Asset
- Packages
- UserSettings
- ProjectSettings

These files should create a copy of the sim if copy and replaced into a new unity project in unity version **2022.3.48f1**.

The Unity project uses Unity Perception and some Unity Blender Images, so you may need to 
- re-add the blender files to the project
- re-add the images to the blender files to make it work correctly.

The blender files folder contains all the blender files used in the project
- it technically shouldn't need to be added because it should already be in the asset files of the unity project.

The json_yoloV5 file contains
- JsonToYolo5: Which contains a python script that converts Json files to readable files for YoloV5
- yoloV5 converter: Which contains folders which the JsonToYolo5 converter imports and exports its files from and into after conversion
