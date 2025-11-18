# Perception Injector

**Perception Injector** is a ROS 2–based research and debugging tool designed to inject *artificial perception manipulations* into an existing navigation pipeline.  
It extends RViz with interactive tools and enhances the LaserScan processing pipeline with custom filters to simulate **virtual objects**, **manipulated scan data**, and **sensor offsets**.

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
Before doing anything else, click **"2D Goal Pose"** in RViz so the first TF transforms get published and Nav2 does not time out.

---

# Usage

### Offset Panel
In the lower-left corner of RViz you will find sliders to modify positional and rotational offsets.  
Use them to simulate drift, TF errors, or sensor calibration issues.  
Click **Reset Offsets** to restore default values.

### Rectangle Tool
In the RViz toolbar you’ll find the **Rectangle Tool**.

With it you can:
- place a virtual object anywhere on the map,  
- set width, height, and yaw,  
- inject synthetic LaserScan hits,  
- observe the impact on the local costmap and Nav2 path planning.

---

# Container Commands

### Stop all containers
```bash
docker compose -f docker/docker-compose.yaml stop
```

### Stop everything and remove images + volumes
```bash
docker compose -f docker/docker-compose.yaml down --rmi all --volumes
```
