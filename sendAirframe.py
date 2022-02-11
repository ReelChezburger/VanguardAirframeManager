import os
import json
import shutil

# Creates a config file if one does not exist
if not os.path.exists("VanguardAirframeManager.json"):
    print("It appears this is your first time running this program\n")
    # writes necessary data to dictionary
    configDict = {
        "path": input("Enter your XPlane path here: ")
    }
    # stores data in json file
    with open('VanguardAirframeManager.json', 'w') as outfile:
        json.dump(configDict, outfile)
        outfile.close()

# Opens json file and reads data
with open('VanguardAirframeManager.json') as infile:
    config = json.load(infile)
    infile.close()

# Gets XPlane path from data
xPlanePath = config.get("path")

# Determines airframe to send
airframeToSend = input("Which airframe would you like to send?: ")

# Finds airframe in airframe.db
airframeDB = open(xPlanePath + '\\Output\\CL650\\airframes\\airframe.db', 'r')
lineNumber = 1
for line in airframeDB:
    if "airframe" in line:
        if airframeToSend in line:
            airframeID = line.split("/")[1]
            break
    lineNumber += 1
airframeDB.close()

# Finds data to output
airframeData = ""
airframeDB = open(xPlanePath + '\\Output\\CL650\\airframes\\airframe.db', 'r')
for line in airframeDB:
    line = line.split("\n")[0]
    if "airframe" in line:
        if airframeID == line.split("/")[1]:
            if "state" in line:
                if line.split("/")[3] == "0":
                    airframeData = airframeData + line + "\n"
            else:
                airframeData = airframeData + line + "\n"
                if "uuid" in line:
                    airframeUUID = line.split("= ")[1]
airframeDB.close()

# Writes the data to output file
airframeData = airframeData[:-2]
try:
    shutil.rmtree(os.getcwd() + '\\output')
except:
    print("")
os.mkdir(os.getcwd() + '\\output')
os.mkdir(os.getcwd() + '\\output\\' + airframeToSend)
try:
    dataFile = open('output/' + airframeToSend + '/airframe.db.txt', 'w')
except:
    print("")
dataFile.write(airframeData)
dataFile.close()

#Copy UUID folder
src = xPlanePath + '\\Output\\CL650\\airframes\\' + airframeUUID
shutil.copytree(src, os.getcwd() + '\\output\\' + airframeToSend + '\\' + airframeUUID, copy_function = shutil.copy)

#compress files
shutil.make_archive(airframeToSend, "zip", os.getcwd() + '\\output', airframeToSend)
shutil.move(os.getcwd() + '\\' + airframeToSend + '.zip', os.getcwd() + '\\output\\')
shutil.rmtree(os.getcwd() + '\\output\\' + airframeToSend)