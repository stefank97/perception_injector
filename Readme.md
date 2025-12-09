# Perception Injector

**Perception Injector** is a ROS 2–based research and debugging tool designed to inject *artificial perception manipulations* into an existing navigation pipeline.  
It extends RViz with interactive tools and enhances the LaserScan processing pipeline with custom filters to simulate **virtual objects**, **manipulated scan data**, and **localization offsets**.

This makes it possible to evaluate how robust a robot’s navigation and localization stack is when exposed to spoofed sensor data or environmental anomalies—without touching any real hardware. The simulation environment also performs continuous ARP-based network manipulation (arpspoof) inside the container to disrupt traffic between the localization and navigation components in order to intercept and tamper data.


This package depends on third-party packages. Please refer to the Notice.md file.

## Features
- 🟦 **RViz Rectangle Tool**  
  Interactively place virtual objects into the occupancy map. These objects are injected into the LaserScan and appear in the local costmap—even though they are not part of the static map.

- 🎚️ **Offset Panel**  
  Apply controlled offsets to TF frames and the AMCL pose and observe how navigation reacts to drift.

- 🧪 **Fully containerized simulation environment**  
  Stage simulator, Nav2, RViz, custom nodes, and all dependencies are deployed automatically.

---

# Setup

### 1. Allow Docker access to your X11 display
To allow docker to start programs with GUIs:
```bash
sudo xhost +local:docker
```

### 2. Run the automatic setup script  
Located at: `perception_injector/scripts/setup.sh`

```bash
cd scripts/
./setup.sh
```

### 3. Open the project in VS Code & enter the Devcontainer
Use one of the following:

- Click **Reopen in Container** (bottom right), or  
- Press `Ctrl + Shift + P` → `>Reopen in Container`

☕ This may take a while — grab a coffee.

### 4. Stop all containers once, then reopen the Devcontainer
```bash
docker compose -f docker/docker-compose.yaml stop
```

After reopening, RViz and Stage will launch automatically.  
Before doing anything else, click **"2D Goal Pose"** and let the robot drive across the map in RViz, so the first TF transforms get published and Nav2 does not time out. It needs to make some distance, so at least send it down the hallway. If it stops after a few meters do not panic - thats where the attacker node sets in, it will continue after a few seconds.

### 5. Discovery Server

If you want to use the discovery server (which is initially disabled), you need to add the service "discovery" to the `docker-compose.yaml` and set the following environment variables:

dds.env:
```bash
FASTRTPS_DEFAULT_PROFILES_FILE=/ws/src/fastdds/server/fdds_server.xml
```
default.env & gui.env:
```bash
FASTRTPS_DEFAULT_PROFILES_FILE=/ws/src/fastdds/client/fastdds_client.xml
ROS_DISCOVERY_SERVER=172.16.0.253:11811
```

### 6. Eclipse Cyclone DDS

There is also a file provided at `/ws/src/cyclonedds` if you want to try and play around with the cyclone DDS middleware (standard is fast DDS). In order for it to work, you need to add the following to each Dockerfile:
```bash
RUN apt-get update && apt-get install -y ros-jazzy-rmw-cyclonedds-cpp
```
Also, to each .env file, add these lines:
```bash
RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
CYCLONEDDS_URI=file:///ws/src/cyclonedds/cyclone_no_shm.xml
```

---

# Usage

### Offset Panel
In the lower-left corner of RViz you will find sliders to modify positional and rotational offsets.  
Use them to simulate drift and watch the robot react to it.
Click **Reset Offsets** to restore default values.

### Rectangle Tool
In the RViz toolbar you’ll find the **Rectangle Tool**.

With it you can:
- place a virtual object anywhere on the map (through injecting synthetic LaserScan hits),  
- set width, height, and yaw (in the 'Tool Properties'),
- observe the impact on the local costmap and Nav2 path planning.

---

# Container Commands

### Stop all containers
```bash
docker compose -f docker/docker-compose.yaml stop
```

### Stop all containers and remove images + volumes
```bash
docker compose -f docker/docker-compose.yaml down --rmi all --volumes
```
