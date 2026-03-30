*This project has been created as part of the 42 curriculum by maaugust.*

<div align="center">
  <img src="https://raw.githubusercontent.com/rfs-hybrid/42-Common-Core/main/assets/covers/cover-fract-ol-bonus.png" alt="Fract'ol Cover" width="100%" />
</div>

<div align="center">
  <h1>🌌 Fract'ol: Computer Graphics Fractals</h1>
  <img src="https://img.shields.io/badge/Language-C-blue" />
  <img src="https://img.shields.io/badge/Grade-125%2F100-success" />
  <img src="https://img.shields.io/badge/Norminette-Passing-success" />
</div>

---

## 💡 Description
**Fract'ol** is a computer graphics project in the 42 curriculum designed to introduce students to the concept of complex numbers, mathematical rendering, and window management using the 42 **MiniLibX** library.

The goal of the project is to create a high-performance fractal renderer. By translating screen coordinates into the complex plane, the program calculates the escape trajectory of mathematical sequences (like $`Z = Z^2 + C`$) to draw graphically stunning, infinitely zoomable representations of the Mandelbrot and Julia sets. 

Because rendering fractals requires hundreds of thousands of calculations per frame, a major focus of this project is **algorithmic optimization**—ensuring the application remains buttery smooth even at extreme zoom depths.

---

## 📑 Features

### 🔹 Mandatory Features
* **Core Sets:** Fully implements the **Mandelbrot** and **Julia** fractals.
* **Infinite Zoom:** Allows infinite zooming into the center of the fractal using the mouse wheel, scaling the complex plane without losing aspect ratio.
* **Strict Parameter Parsing:** Features a custom, bulletproof `ft_atod` parser that rejects garbage inputs, whitespace errors, and invalid formatting while displaying clean usage instructions.
* **Memory Safety:** 100% leak-free. Gracefully handles MiniLibX initialization failures, window crosses, and `ESC` key exits.
* **Optimized Rendering:** Uses a direct memory-address pixel-putting technique (bypassing the slow `mlx_pixel_put`) and an `enum`-based routing system to eliminate slow string comparisons in the rendering loop.

### 🚀 Bonus Features
* **Expanded Fractal Library:** Includes mathematical implementations of the **Burning Ship**, **Tricorn**, **Phoenix**, and a visual **Phoenix Variant**.
* **Dynamic Mouse Zoom:** Upgrades the zoom calculation so the fractal scales directly toward the exact position of the user's mouse cursor.
* **Keyboard Navigation:** Allows the user to pan the complex plane view using the Arrow Keys or `W` `A` `S` `D`.
* **Advanced Color Controls:** Maps `Page Up` and `Page Down` to cycle through an extensive array of custom color palettes. Users can also dynamically shift the color shading intensity using `Home` / `End`, or toggle a grayscale mode with `G`.
* **Interactive Adjustments:** Allows the user to manually increase or decrease the maximum rendering iterations (`Q` / `E`). For the Phoenix sets, the mathematical $`\delta`$ (delta) parameter can be warped and morphed in real-time using `[` and `]`.
* **Reset State:** Maps `R` to instantly revert the fractal back to its original zoom, position, and mathematical parameters (including the delta state).
* **Dynamic Resolution:** Prompts the user via `stdin` upon launch to select from multiple window resolutions (up to 1680x1050), protected by strict boolean parsing.

---

## 🧠 Algorithm & Data Structure

### Data Structure: Centralized `t_fractal`
To comply with the strict 42 Norm (max 4 parameters per function) while avoiding forbidden global variables, the entire application state is managed via a central `t_fractal` structure. It acts as the single source of truth, holding the MLX window pointers, image buffers, complex mathematical variables ($`Z`$ and $`C`$), zoom multipliers, shift offsets, and the current color palette array.

### Algorithm: The Escape-Time Algorithm
Fractals are rendered using the Escape-Time algorithm. For every single pixel on the screen:
1. **Coordinate Mapping:** The pixel's $`(X, Y)`$ screen coordinates are mathematically mapped to $`(Real, Imaginary)`$ coordinates on the Cartesian complex plane.
2. **Iteration:** A specific mathematical function (e.g., $`Z_{n+1} = Z_n^2 + C`$) is applied repeatedly.
3. **Escape Check:** If the magnitude of the complex number exceeds the escape radius ($`Z_{re}^2 + Z_{im}^2 > 4.0`$), it has "escaped" and the loop breaks.
4. **Coloring:** The pixel is colored based on exactly *how many* iterations it took to escape. If it never escapes before reaching `max_iter`, it is considered part of the fractal set and colored black.

### Optimization 1: Direct Memory Image Buffering
Using the standard `mlx_pixel_put` function is notoriously slow because it attempts to push pixels to the X-Server one by one. To achieve fluid 60FPS rendering and zooming, this algorithm writes directly to RAM. 
* It uses `mlx_get_data_addr` to find the starting memory address of an image buffer.
* For each pixel, it calculates the exact memory offset: `(y * line_length + x * (bits_per_pixel / 8))`.
* It assigns the calculated integer color directly to that memory address. Once the entire loop is finished, the fully drawn image is pushed to the window in a single `mlx_put_image_to_window` call.

### Optimization 2: Enum-Based Execution Routing
In a window of 1024x768, the rendering loop fires over 780,000 times per frame. If the program used string comparisons (`ft_strncmp`) inside the loop to check which fractal to draw, the CPU would be crippled. 
* Instead, during the parsing phase, the fractal type is resolved once and assigned to an `e_fractal_type` enum.
* Inside the rendering loop, the program relies on ultra-fast integer comparisons (`if (frac->type == MANDELBROT_TYPE)`) to instantly route to the correct mathematical algorithm.

---

## 🖼️ Gallery & Demos

### 🍎 The Mandelbrot Set
*Visualizing the sequence $`Z_{n+1} = Z_n^2 + C`$ starting with $`Z_0 = 0`$.*

<table align="center">
  <tr>
    <th align="center">Mathematical Reference</th>
    <th align="center">My Fract-ol Render</th>
  </tr>
  <tr>
    <td align="center"><img src="assets/img/reference_mandelbrot.png" alt="Reference Overview" width="400"/></td>
    <td align="center"><img src="assets/img/fractol_mandelbrot.png" alt="My Overview" width="400"/></td>
  </tr>
  <tr>
    <td align="center"><img src="assets/img/reference_mandelbrot2.png" alt="Reference Zoom" width="400"/></td>
    <td align="center"><img src="assets/img/fractol_mandelbrot2.png" alt="My Zoom" width="400"/></td>
  </tr>
</table>

---

### 🌌 The Julia Set
*Visualizing the sequence $`Z_{n+1} = Z_n^2 + C`$ where $`C`$ is a fixed complex constant.*

<table align="center">
  <tr>
    <th align="center">Mathematical Reference</th>
    <th align="center">My Fract-ol Render</th>
  </tr>
  <tr>
    <td align="center">
      <img src="assets/img/reference_julia.png" alt="Reference Overview" width="322"/><br>
      <em>C = -0.4 + 0.6i</em>
    </td>
    <td align="center">
      <img src="assets/img/fractol_julia.png" alt="My Overview" width="400"/><br>
      <em>C = -0.4 + 0.6i</em>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="assets/img/reference_julia2.png" alt="Reference Zoom" width="322"/><br>
      <em>C = 0.285 + 0.01i</em>
    </td>
    <td align="center">
      <img src="assets/img/fractol_julia2.png" alt="My Overview" width="400"/><br>
      <em>C = 0.285 + 0.01i</em>
    </td>
  </tr>
</table>

---

### 🔺 The Tricorn (Mandelbar)
*Visualizing the complex conjugate variation $`Z_{n+1} = \bar{Z}_n^2 + C`$.*

<table align="center">
  <tr>
    <th align="center">Mathematical Reference</th>
    <th align="center">My Fract-ol Render</th>
  </tr>
  <tr>
    <td align="center"><img src="assets/img/reference_tricorn.png" alt="Reference Overview" width="322"/></td>
    <td align="center"><img src="assets/img/fractol_tricorn.png" alt="My Overview" width="400"/></td>
  </tr>
  <tr>
    <td align="center"><img src="assets/img/reference_tricorn2.png" alt="Reference Zoom" width="322"/></td>
    <td align="center"><img src="assets/img/fractol_tricorn2.png" alt="My Zoom" width="400"/></td>
  </tr>
</table>

---

### 🚢 The Burning Ship
*Visualizing the absolute value variation $`Z_{n+1} = (|Re(Z_n)| + i|Im(Z_n)|)^2 + C`$.*

<table align="center">
  <tr>
    <th align="center">Mathematical Reference</th>
    <th align="center">My Fract-ol Render</th>
  </tr>
  <tr>
    <td align="center"><img src="assets/img/reference_burning_ship.png" alt="Reference Overview" width="400"/></td>
    <td align="center"><img src="assets/img/fractol_burning_ship.png" alt="My Overview" width="400"/></td>
  </tr>
  <tr>
    <td align="center"><img src="assets/img/reference_burning_ship2.png" alt="Reference Zoom" width="400"/></td>
    <td align="center"><img src="assets/img/fractol_burning_ship2.png" alt="My Zoom" width="400"/></td>
  </tr>
</table>

---

### 🦅 The Phoenix Set
*Visualizing the recurrence relation $`Z_{n+1} = Z_n^2 + C + \delta * Z_{n-1}`$.*

<table align="center">
  <tr>
    <th align="center">Mathematical Reference</th>
    <th align="center">My Fract-ol Render</th>
  </tr>
  <tr>
    <td align="center">
      <img src="assets/img/reference_phoenix.png" alt="Reference Overview" width="430"/><br>
      <em>C = 0.5667, delta = -0.5</em>
    </td>
    <td align="center">
      <img src="assets/img/fractol_phoenix.png" alt="My Overview" width="400"/><br>
      <em>C = 0.5667, delta = -0.5</em>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="assets/img/reference_phoenix2.png" alt="Reference Overview" width="322"/><br>
      <em>C = -0.4 + 0.1i, delta = 0.2955</em>
    </td>
    <td align="center">
      <img src="assets/img/fractol_phoenix2.png" alt="My Overview" width="400"/><br>
      <em>C = -0.4 + 0.1i, delta = 0.2955</em>
    </td>
  </tr>
</table>

---

### 🦋 The Phoenix Variant (Custom Mutation)
*Using specific `C` and `delta` parameters to compare standard Phoenix geometry against my custom modified imaginary recurrence.*

<table align="center">
  <tr>
    <th align="center">Mathematical Reference (Standard)</th>
    <th align="center">My Fract-ol Render (Variant)</th>
  </tr>
  <tr>
    <td align="center">
      <img src="assets/img/reference_phoenix3.png" alt="Reference Butterfly" width="322"/><br>
      <em>C = 0.4, delta = -0.25</em>
    </td>
    <td align="center">
      <img src="assets/img/fractol_phoenix_variant.png" alt="My Butterfly Variant" width="400"/><br>
      <em>C = 0.4, delta = -0.25</em>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="assets/img/reference_phoenix4.png" alt="Reference Stretch" width="322"/><br>
      <em>C = 0.1 + 0.6i, delta = -0.35</em>
    </td>
    <td align="center">
      <img src="assets/img/fractol_phoenix_variant2.png" alt="My Stretched Variant" width="400"/><br>
      <em>C = 0.1 + 0.6i, delta = -0.35</em>
    </td>
  </tr>
</table>

---

## 🎬 Interactive Showcase

*A complete demonstration of the `fract-ol` bonus features running in real-time.*


<div align="center">
  <video src="https://github.com/user-attachments/assets/051670da-9dc6-421a-9ca4-268f170b758b" width="800" controls="controls"></video>
</div>

**Features demonstrated in this run:**
* **Custom Initialization:** Terminal argument parsing with a custom interactive resolution prompt.
* **Flawless Optimization:** Smooth, high-FPS infinite zooming and panning using the MiniLibX image API.
* **Algorithmic Variety:** Instant real-time cycling through custom mathematical color palettes.
* **Continuous Recalculation:** Dynamic, real-time morphing of the `delta` parameter using keyboard hooks.

---

## 🛠️ Instructions

### 📦 Installation
To compile the project, run the following commands in the root of the repository.

* To build the **mandatory** executable (`fractol`):
```bash
make
```

* To build the **bonus** executable (`fractol_bonus`):
```bash
make bonus
```

### 🧹 Cleaning
* `make clean`: Removes the compiled object files (`.o`).
* `make fclean`: Removes object files, the executables, and cleans the embedded `libft`.
* `make re`: Performs a clean re-build.

### 💻 Usage

**Mandatory & Bonus:**
```bash
./fractol mandelbrot
./fractol julia <real_value> <imaginary_value>
./fractol_bonus mandelbrot
./fractol_bonus julia <real_value> <imaginary_value>
```
*Example: `./fractol julia -0.8 0.156`*

**Bonus Only:**
```bash
./fractol_bonus tricorn
./fractol_bonus "burning ship"
./fractol_bonus phoenix <real> <imag> <delta>
./fractol_bonus "phoenix variant" <real> <imag> <delta>
```
*Example: `./fractol_bonus phoenix 0.5667 0.0 -0.5`*

### 🎮 Controls
| Action | Keybind |
| :--- | :--- |
| **Pan Camera** | `W` `A` `S` `D` or `Arrow Keys` |
| **Zoom In / Out** | `Mouse Scroll Wheel` |
| **Cycle Palettes** | `Page Up` / `Page Down` |
| **Adjust Color Shade** | `Home` (Increase) / `End` (Decrease) |
| **Grayscale Toggle** | `G` |
| **Change Max Iterations**| `Q` (Decrease) / `E` (Increase) |
| **Modify Delta (Phoenix)**| `[` (Decrease) / `]` (Increase) |
| **Reset View/Settings** | `R` |
| **Exit** | `ESC` or Window `X` |

---

### 🧪 Testing & Edge Cases
Because `fract-ol` relies heavily on real-time user input and memory management, rigorous testing is essential to ensure stability. You are encouraged to push the program to its limits by testing the following scenarios:

#### 1. Input Parsing & Validation
The program must securely handle garbage input without segmentation faults. Test the parser by throwing invalid arguments at it:
* Invalid fractal names: `./fractol unknown`
* Incorrect argument counts: `./fractol julia 0.285` (missing the imaginary value)
* Non-numeric characters: `./fractol julia 0.4a 0.6`
* **Expected Result:** The program should instantly reject the input, print a clean usage menu to `stdout`/`stderr`, and exit gracefully with no memory leaks.

#### 2. The Rendering Buffer Test
When zooming, panning, or changing colors, the window should update instantaneously.
* **What to look for:** The image must render **all at once**. If you can visually see the fractal drawing itself "pixel by pixel" from top to bottom, it means the slow `mlx_pixel_put` function is being used. This implementation uses direct memory addressing, guaranteeing instant, single-frame pushes to the window.
* Verify that the shapes generated perfectly match the mathematical reference images documented in the gallery above.

#### 3. Dynamic Sets (Go Wild!)
The `julia` and `phoenix` sets rely on user-defined constant/delta values. 
* Don't just stick to the documented examples! Throw wild, highly specific floating-point values into the terminal (e.g., `./fractol_bonus julia -0.835 -0.2321`). 
* Use the `[` and `]` keys in the Phoenix sets to continuously warp the math in real-time and observe the dynamic structural changes.

#### 4. Event Stability & Exit Conditions
Mash the keyboard. Cycle the palettes rapidly while simultaneously zooming and panning.
* **Expected Result:** The program should never freeze, crash, or exhibit unexpected behavior.
* **Strict Exit Handling:** The program must *only* terminate when the user explicitly presses the `ESC` key or clicks the window's `X` (close) button. Any other key press should be safely ignored or handled by the program.

#### 5. Memory Leak Verification (Valgrind)
Like all 42 projects, `fract-ol` must be 100% leak-free. You can verify this using Valgrind, but **please read the warning below**.

```bash
valgrind --leak-check=full --show-leak-kinds=all ./fractol mandelbrot
```

> **⚠️ IMPORTANT VALGRIND WARNING:** Running a graphical application through Valgrind will make the program **extremely slow**. Valgrind acts as an incredibly heavy virtual machine that tracks every single byte of memory. Because this program recalculates ~780,000 pixels every time you zoom or move, running it through Valgrind will drop the frame rate to a crawl. **This is normal and is not an optimization failure.** Test the memory safety with Valgrind, then run the executable normally to evaluate the true rendering speed.

---

### 🚨 The Norm
Moulinette relies on a program called `norminette` to check if your files comply with the 42 Norm. Every single `.c` and `.h` file must pass this check. If there is a norm error, you will receive a 0.

**The 42 Header:**
Before writing any code, every file must start with the standard 42 header. `norminette` will automatically fail any file missing this specific signature.
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:19:45 by maaugust          #+#    #+#             */
/*   Updated: 2025/07/07 17:18:36 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
```

Run the following command in the root of your repository to check all your files at once:
```bash
norminette -R CheckForbiddenSourceHeader srcs/ bonus/ includes/
```

---

## 📚 Resources & References

**System Manuals:**
* `man 3 math` - The standard C math library programmer's manual. Essential for understanding compilation links (`-lm`) when dealing with advanced mathematical formulas.
* `man ./path_to_mlx/man/man3/mlx.3` / `man ./path_to_mlx/man/man3/mlx_new_window` / `man ./path_to_mlx/man/man3/mlx_new_image` / `man ./path_to_mlx/man/man3/mlx_pixel_put`  - Local manual pages provided by the 42 `minilibx-linux` package detailing the graphical API functions.
  * Because `minilibx` is a custom 42 library and not a standard Linux system library, typing `man mlx` natively will fail. However, the repository ships with raw manual files! You can read them by pointing the `man` command directly to the files inside the `man/man3/` directory of your cloned `minilibx` folder.

**Articles & Guides:**
* **[Mandelbrot Set (Wikipedia)](https://en.wikipedia.org/wiki/Mandelbrot_set):** Core formulas and definitions.
* **[Julia Set (Wikipedia)](https://en.wikipedia.org/wiki/Julia_set):** Understanding the relationship between $Z$ and the constant $C$.
* **[Burning Ship Fractal (Wikipedia)](https://en.wikipedia.org/wiki/Burning_Ship_fractal):** The absolute value variation.
* **[Mandelbrot Set (Paul Bourke)](https://paulbourke.net/fractals/mandelbrot/):** An excellent deep dive into the math and rendering logic of the Mandelbrot set.
* **[Julia Set (Paul Bourke)](https://paulbourke.net/fractals/juliaset/):** Detailed explanation and visual examples of Julia sets.
* **[Tricorn (Paul Bourke)](https://paulbourke.net/fractals/tricorn/):** Mathematical overview of the Tricorn (Mandelbar) fractal.
* **[Burning Ship (Paul Bourke)](https://paulbourke.net/fractals/burnship/):** Insights into the Burning Ship calculation.
* **[Phoenix & Julia (Paul Bourke)](https://paulbourke.net/fractals/phoenix_julia/):** Reference for the recurrence relation used in Phoenix sets.
* **[Color Interpolation](https://lodev.org/cgtutor/color.html):** Techniques for applying trigonometric shading to RGB channels to create beautiful, continuous color palettes.
* **[MiniLibX (42Docs)](https://harm-smits.github.io/42docs/libs/minilibx):** The holy grail for understanding the 42 graphical library, events, hooks, and fast image drawing.
* **[Understanding the MiniLibX by jalal92 (Medium)](https://medium.com/@jalal92/understanding-the-minilibx-a-practical-dive-into-x-window-programming-api-in-c-cb8a6f72bec3):** A great practical dive into the X-Window programming API in C.
* **[Fract'ol: Creating graphically beautiful fractals by Léo Gaudin (Medium)](https://medium.com/@leogaudin/fract-ol-creating-graphically-beautiful-fractals-6664b6b045b5):** A fantastic, student-written guide covering the exact 42 project requirements.
* **[Fract'ol by Jalal92 (Medium)](https://medium.com/@jalal92/fractol-22a21a1ad5bd):** Another great breakdown of the project architecture and math logic.

**Video Tutorials:**
* **[YouTube - Introduction to the minilibX by Oceano](https://www.youtube.com/watch?v=bYS93r6U0zg):** A super practical introduction to X-Window programming in C using the MiniLibX API.
* **[YouTube - fractol: render beautiful fractals in C by Oceano](https://www.youtube.com/watch?v=ANLW1zYbLcs):** A legendary 2-hour long complete walkthrough of the project, highly recommended for understanding how to bind complex math to the MiniLibX window.

**42 Standards:**
* **[42 Norm V4](https://cdn.intra.42.fr/pdf/pdf/96987/en.norm.pdf):** The strict coding standard for 42 C projects.
* **[Official 42 Norminette Repository](https://github.com/42School/norminette):** The open-source linter enforcing the strict 42 coding standard.

---

### 🤖 AI Usage & Transparency
In the spirit of transparency and the learning objectives of the 42 curriculum, here is how AI tools were utilized during this project:

* **Code Architecture & Review:** Used as a sounding board to identify performance bottlenecks (like swapping string comparisons for `enum` checks inside the rendering loop) and to ensure strict adherence to the mandatory vs. bonus file separation rules.
* **Documentation & Build Automation:** Assisted in generating portfolio-ready Doxygen comments, formatting this `README.md` layout, and writing a highly robust, dynamic `Makefile` capable of auto-fetching dependencies and cleanly routing object files.
* **Zero Core Logic Generation:** **No core mathematical logic was generated by AI**. The fractal algorithms, complex plane translations, mouse tracking math, and bitwise color shifting were 100% manually written. This ensures a fundamental, defendable understanding of the project's graphical concepts.
