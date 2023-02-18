# TM2020-TAS

TM2020-TAS is a TAS tool for Trackmania 2020, written in C++/Python.

## How does it work?

TM2020-TAS uses a combination of replay input extraction and memory reading to assist in TASes.

### **NOTE:** *These instructions are not final as several of these features have not yet been implemented, so everything is subject to change.*

1. Open Trackmania, and load the map you want to TAS.
2. Open the memory sniffer application. This will attach to Trackmania and monitor the car's location. This is useful for TAS splicing later in the process.
3. After you've completed the map, save the replay.
4. Open the replay file with the replay input extractor. This will extract all user inputs during the run.
5. Open the splicer. This will take in both the monitored car location and the extracted replay inputs. With both of these, you can see exactly where your car was at any point in time.
6. With the splicer open, you can make a cut at any point, allowing the TAS to play a certain section of the map for you.
7. If you want to simply optimize a run, you can run the brute force function which will slightly vary the inputs to try and find a faster solution. This is a lengthy process, but is fully automatic.
8. You're done! Just have the TAS playback the final inputs in the game, save the replay, and enjoy!

## What features have been completed?

As stated above, this tool is very much a work in progress, but this is what has been completed and what is left to do.

| Feature | Completed? |
| ------- | ---------- |
| Replay Input Extraction | Partially Implemented |
| Car Location Monitoring | Completed |
| TAS Replay | Not Implemented |
| Brute Force | Not Implemented |
| Cohesive GUI | Not Implemented |