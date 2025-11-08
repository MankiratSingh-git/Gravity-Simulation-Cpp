#  Gravity Simulation (C++) — Test Release v0.1

This project is a **2D gravity simulator** written entirely in **C++20**, built from scratch without any external libraries.  
It numerically simulates gravitational attraction between multiple bodies according to **Newton’s Law of Universal Gravitation**.

This release implements the **core physics engine** and a **console-based Sun–Earth test case**.

---

##  Overview

The goal of this project is to simulate the motion of celestial bodies (like planets and stars) under mutual gravity.  
Each body moves based on the sum of forces acting on it from every other body, updated in discrete time steps.

This version focuses on:
- Building the physics engine from scratch  
- Testing the Sun–Earth orbit  
- Debugging the core logic before visualization

---

##  Methodology

### 1️ Force Calculation

For each pair of bodies **i** and **j**, the gravitational force is computed as:

\[
\vec{F} = G \frac{m_i m_j}{(r^2 + s^2)^{3/2}} \vec{r}
\]

Where:
- \( G \) = gravitational constant  
- \( s \) = softening factor (to prevent singularities at very small distances)  
- \( \vec{r} \) = displacement vector between bodies  

Each body’s acceleration is updated using:
\[
\vec{a} = \frac{\vec{F}}{m}
\]

---

### 2️ Integration (Motion Update)

The position and velocity are updated each step using a **semi-Verlet-like integration**:

\[
\vec{v}(t+\Delta t) = \vec{v}(t) + \vec{a}\Delta t
\]

\[
\vec{x}(t+\Delta t) = \vec{x}(t) + \vec{v}(t)\Delta t + 0.5\vec{a}\Delta t^2
\]

This provides a good balance between simplicity and stability for orbital motion.

---

### 3️ Softening

A small constant `s` is added in the denominator to prevent infinite force when two bodies come extremely close.  
This avoids numerical instability while having negligible effect at larger distances.

---


## Components

### Vec2
A 2D vector class for physics math.

**Implements:**
- `+`, `-`, `*`, `/` operators  
- `length()` and `normalize()`  
- Used for position, velocity, and acceleration

---

### Body
Represents a single celestial object.

**Members:**
- `std::string name` — identifier  
- `double mass` — mass of the body  
- `Vec2 pos, vel, acc` — motion data  

**Methods:**
- `applyForce(Vec2 F)` — adds force to acceleration  
- `resetAcc()` — clears acceleration  
- `update(double dt)` — updates velocity and position

---

### Simulation
Manages the entire system of bodies.

**Members:**
- `std::vector<Body> bodies`
- `double G` — gravitational constant
- `double s` — softening factor
- `double time` — simulation time

**Function:**
`step(double dt)`  
- Resets accelerations  
- Calculates all pairwise forces  
- Applies them and updates all bodies  

---

## Example — Sun and Earth

The `SunEarth.cpp` example sets up a simple orbit:

```cpp
sim.G = 1.0;
sim.bodies.push_back(Body("Sun",   1000, Vec2(0, 0)));
sim.bodies.push_back(Body("Earth", 1, Vec2(100, 0), Vec2(0, 3.16)));
```

This approximates a near-circular orbit around the Sun.

---

## Sample Output

```
t       Earth.x Earth.y vx      vy      dist
0.000   100.000 0.000   0.000   3.160   100.000
1.000    99.950 3.159   -0.100  3.158   100.000
2.000    99.800 6.316   -0.200  3.154   100.000
3.000    99.550 9.466   -0.300  3.146   99.999
...
```

The Earth starts moving around the Sun, with a stable orbit at roughly the same distance.

---

## 🧩 How to Run

Compile and run the test simulation:
Using MSVC:

```bash
cl /std:c++20 SunEarth.cpp /Fe:GravitySim.exe
GravitySim.exe
```

That’s all — the simulation prints live data to the console.

---

## Default Parameters

| Variable | Meaning | Default |
|-----------|----------|----------|
| `G` | Gravitational constant | 1.0 |
| `dt` | Time step | 0.01 |
| `s` | Softening factor | 1e-4 * scale |
| `scale` | Positional scale | 1000 |

---


## Notes

- The simulation runs on a simple **O(n²)** algorithm (pairwise gravity).  
  Efficient for small systems, but will need optimization later.  
- Using a smaller time step (`dt`) increases accuracy but slows the simulation.  
- The results are deterministic for a given setup.

---


###  Author
Developed by **Mankirat Singh**  
