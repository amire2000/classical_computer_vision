# Session 1: Pixels and Image Matrices

**Time:** about 2 hours  
**Prerequisite:** complete [Module 0](../00_setup_environment/index.md).

This session teaches the storage model behind an image before introducing an
image-library API. Every hands-on exercise uses only the C++20 standard
library, fixed data, and a single source file.

---

## Goals

By the end of this session, you can:

- Explain why a grayscale image is a grid of `height × width` pixel values.
- Find a pixel in row-major storage with `row * width + column`.
- Explain why an RGB pixel stores three adjacent channel values.
- Relate these ideas to OpenCV's `rows`, `cols`, `channels()`, and `step`.

---

## Core idea

A 2 × 3 grayscale image has two rows and three columns:

```text
row 0: 10  11  12
row 1: 20  21  22
```

It contains six pixels. In **row-major storage**, the rows are placed one after
another:

```text
10  11  12  20  21  22
```

The pixel at `(row, column)` has index `row * width + column`. For example,
`(1, 2)` in a three-column image has index `1 * 3 + 2 = 5`.

Think of the vector as one long shelf. It does not store separate row objects;
the image width tells us where each new row begins. With width `3`, row `0`
starts at index `0`, row `1` starts at index `3`, and a later row `2` would
start at index `6`.

| Coordinate | Calculation | Vector index | Stored value |
| --- | --- | ---: | ---: |
| `(0, 0)` | `0 * 3 + 0` | 0 | 10 |
| `(0, 1)` | `0 * 3 + 1` | 1 | 11 |
| `(0, 2)` | `0 * 3 + 2` | 2 | 12 |
| `(1, 0)` | `1 * 3 + 0` | 3 | 20 |
| `(1, 1)` | `1 * 3 + 1` | 4 | 21 |
| `(1, 2)` | `1 * 3 + 2` | 5 | 22 |

The multiplication skips all complete rows before the requested row. The
addition then moves across the requested column inside that row. This is why
`row * width + column` works: every complete earlier row contains exactly
`width` values.

For an RGB image, each pixel has three adjacent values, so first find the
pixel's row-major position and then multiply by the channel count:

```text
first channel index = (row * width + column) * channels
```

For example, imagine a one-row, two-pixel RGB image:

```text
pixel (0, 0): red = 10, green = 20, blue = 30
pixel (0, 1): red = 40, green = 50, blue = 60
```

In the common **interleaved** layout, the three channel values belonging to
one pixel stay together in memory:

```text
memory index:  0   1   2   3   4   5
value:        10  20  30  40  50  60
meaning:       R   G   B   R   G   B
pixel:         (0, 0)      (0, 1)
```

The channels are adjacent because they describe the same location in the
image. Once code finds the first value for a pixel, it can read its red,
green, and blue values at offsets `+0`, `+1`, and `+2` without another
row-major calculation. This layout is practical for code that processes one
pixel at a time.

For pixel `(1, 0)` in a two-column RGB image, this is
`(1 * 2 + 0) * 3 = 6`. Indices `6`, `7`, and `8` are that pixel's red, green,
and blue values. The same memory shape can use a different channel order:
OpenCV commonly stores **BGR**, so indices `6`, `7`, and `8` would mean blue,
green, and red instead. The number and adjacency of channels do not change;
only their meaning and order do.

---

## Build commands

Each file below is complete. From the repository root, compile one with:

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic \
  modules/01_image_foundations/session_01/exercises/01_pixel_count.cpp \
  -o /tmp/01_pixel_count
/tmp/01_pixel_count
```

Starter programs compile but intentionally fail an `assert` until you replace
their `TODO`. Solution programs compile and run successfully with the same
command after replacing `exercises` with `solutions`.

---

## Exercise 1: Count grayscale pixels

For a 2 × 3 grayscale image, replace the `TODO` with the number of stored
pixel values. The completed program prints `2 rows x 3 columns = 6 pixels`.

```cpp
--8<-- "modules/01_image_foundations/session_01/exercises/01_pixel_count.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_01/solutions/01_pixel_count.cpp"
```

</details>

---

## Exercise 2: Find a row-major pixel

The vector represents the grayscale grid from the core idea. Compute the index
of pixel `(1, 2)` and verify that its value is `22`.

```cpp
--8<-- "modules/01_image_foundations/session_01/exercises/02_row_major_index.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_01/solutions/02_row_major_index.cpp"
```

</details>

---

## Exercise 3: Locate an RGB pixel

An RGB image has three consecutive channel values for every pixel. Compute the
first channel index of pixel `(1, 0)`, then verify that its red, green, and blue
values sum to `24`.

```cpp
--8<-- "modules/01_image_foundations/session_01/exercises/03_rgb_pixel.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_01/solutions/03_rgb_pixel.cpp"
```

</details>

---

## OpenCV connection

You do not need OpenCV to complete the exercises. When you do use `cv::Mat`,
the same concepts have familiar names:

| Matrix concept | `cv::Mat` expression |
| --- | --- |
| Height | `image.rows` |
| Width | `image.cols` |
| Channels per pixel | `image.channels()` |
| Bytes between row starts | `image.step` |

For an 8-bit, three-channel BGR image, a row normally needs `cols * 3` bytes.
`step` may be larger when rows contain padding, which is why later sessions
will not assume that all image rows are tightly packed.

---

## Review quiz

<form class="quiz" data-answer="b" data-explanation="A 2 × 3 grayscale image has 2 × 3 individual intensity values.">
  <fieldset>
    <legend>1. How many pixel values are in a 2 × 3 grayscale image?</legend>
    <label><input type="radio" name="session1-q1" value="a"> 5</label><br>
    <label><input type="radio" name="session1-q1" value="b"> 6</label><br>
    <label><input type="radio" name="session1-q1" value="c"> 9</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="c" data-explanation="Row-major storage puts every value from one row before the next row.">
  <fieldset>
    <legend>2. What does row-major storage do?</legend>
    <label><input type="radio" name="session1-q2" value="a"> Stores each color channel in a separate file.</label><br>
    <label><input type="radio" name="session1-q2" value="b"> Stores columns before rows.</label><br>
    <label><input type="radio" name="session1-q2" value="c"> Stores one complete row before the next row.</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="a" data-explanation="For width 3, index = 1 × 3 + 2 = 5.">
  <fieldset>
    <legend>3. What is the row-major index of (1, 2) in an image with width 3?</legend>
    <label><input type="radio" name="session1-q3" value="a"> 5</label><br>
    <label><input type="radio" name="session1-q3" value="b"> 3</label><br>
    <label><input type="radio" name="session1-q3" value="c"> 6</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="b" data-explanation="RGB assigns three values—red, green, and blue—to each pixel.">
  <fieldset>
    <legend>4. How many channels does a normal RGB pixel have?</legend>
    <label><input type="radio" name="session1-q4" value="a"> 1</label><br>
    <label><input type="radio" name="session1-q4" value="b"> 3</label><br>
    <label><input type="radio" name="session1-q4" value="c"> 8</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="c" data-explanation="step is the byte distance from the start of one image row to the start of the next.">
  <fieldset>
    <legend>5. What does cv::Mat::step describe?</legend>
    <label><input type="radio" name="session1-q5" value="a"> The number of image channels.</label><br>
    <label><input type="radio" name="session1-q5" value="b"> The total number of pixels.</label><br>
    <label><input type="radio" name="session1-q5" value="c"> The bytes between the starts of consecutive rows.</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

---

## Completion check

- Explain why the pixel count of a grayscale image is `height * width`.
- Calculate one row-major index without running code.
- Compile and run all three solution files.
- Answer all five quiz questions correctly.

Next: return to the [Module 1 overview](index.md) before starting Session 2.

---

## C++ concepts used in this session

These are C++ language and standard-library tools used in the exercise files;
they are separate from OpenCV.

| C++ feature | Meaning here |
| --- | --- |
| `#include <...>` | Makes declarations from a standard-library header available, such as `std::vector` from `<vector>`. |
| `int main()` | The program's starting function. Returning from it means the program succeeded. |
| `constexpr` | A value known at compile time. `constexpr std::size_t width = 3;` gives the compiler a fixed image width. |
| `const` | A value that cannot be reassigned after it is initialized. The pixel data stays unchanged while the program reads it. |
| `std::size_t` | The standard unsigned integer type for sizes and indexes. It is appropriate for rows, columns, and vector positions. |
| `std::vector<T>` | A growable sequence of values. `std::vector<int>` stores the flattened grayscale pixels in Exercise 2. |
| `std::array<T, N>` | A fixed-size sequence known at compile time. `std::array<int, 12>` stores four RGB pixels with three values each. |
| `values[index]` | The indexing operation that reads one value from a vector or array. The row-major calculation produces this `index`. |
| `std::cout` | The standard output stream. `<<` sends text and values to the terminal. |
| `assert(condition)` | A debug check from `<cassert>`. The program stops when `condition` is false, which makes each exercise's expected result runnable. Defining `NDEBUG` disables assertions, so do not use it for these exercises. |
