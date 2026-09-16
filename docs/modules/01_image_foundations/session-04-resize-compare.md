# Session 4: Resize, Compare, and Diagnose

**Time:** about 2–2.5 hours  
**Prerequisite:** complete [Session 3](session-03-grayscale.md).

This session builds a small, dependency-free image-processing loop: map output
pixels to source pixels, preserve stride, and measure the error against a
reference result.

---

## Goals

By the end of this session, you can:

- Explain nearest-neighbor resizing as output-to-source coordinate mapping.
- Resize a fixed grayscale image with integer arithmetic.
- Diagnose a resize bug caused by confusing width and stride.
- Build an absolute-difference image and interpret zero versus nonzero pixels.

---

## Core idea: each output pixel chooses one input pixel

Nearest-neighbor resizing does not invent a new pixel value. For every output
coordinate, it chooses the corresponding source coordinate:

```text
source_row    = destination_row    * source_height / destination_height
source_column = destination_column * source_width  / destination_width
```

When a 2 × 2 image grows to 4 × 4, each source pixel becomes a 2 × 2 block:

```text
source:                 nearest-neighbor result:
10  20                  10  10  20  20
30  40                  10  10  20  20
                        30  30  40  40
                        30  30  40  40
```

This is fast and preserves exact input values, but it makes blocky edges.

---

## Build commands

Each file below is complete and needs only the C++20 standard library. From the
repository root, compile one with:

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic \
  modules/01_image_foundations/session_04/exercises/01_nearest_coordinate.cpp \
  -o /tmp/01_nearest_coordinate
/tmp/01_nearest_coordinate
```

Starter programs compile but intentionally fail an `assert` until you replace
their `TODO`. Solution programs compile and run successfully with the same
command after replacing `exercises` with `solutions`.

---

## Exercise 1: Map one output coordinate

Map output coordinate `3` from a four-pixel destination to a two-pixel source.
It must select source coordinate `1`.

```cpp
--8<-- "modules/01_image_foundations/session_04/exercises/01_nearest_coordinate.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_04/solutions/01_nearest_coordinate.cpp"
```

</details>

---

## Exercise 2: Resize a 2 × 2 image

Implement the nested loops that create a 4 × 4 nearest-neighbor result. Check
the four corners to confirm that every source pixel reaches the right region.

```cpp
--8<-- "modules/01_image_foundations/session_04/exercises/02_resize_2x2.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_04/solutions/02_resize_2x2.cpp"
```

</details>

---

## Exercise 3: Diagnose a stride bug

The source has width `2` but stride `4` because each row has two padding
elements. The starter uses `width` to find row `1`, so it reads padding. Replace
the broken calculation with the stride-aware one.

```cpp
--8<-- "modules/01_image_foundations/session_04/exercises/03_stride_diagnosis.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_04/solutions/03_stride_diagnosis.cpp"
```

</details>

---

## Exercise 4: Build an absolute-difference image

For matching manual and reference pixels, the difference is zero. A nonzero
value shows how far the two outputs disagree at that location.

```cpp
--8<-- "modules/01_image_foundations/session_04/exercises/04_absolute_difference.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_04/solutions/04_absolute_difference.cpp"
```

</details>

---

## Timing observation

Timing is useful for comparison, not as a fixed pass/fail score: different
computers, compiler versions, and background processes change the result. Time
the same operation several times, then compare approaches on the same machine.

```cpp
const auto start = std::chrono::steady_clock::now();
// Run the resize loop here.
const auto elapsed = std::chrono::steady_clock::now() - start;
```

Keep row-major traversal in the inner loop when possible. It reads nearby
memory in order, which is usually friendlier to CPU caches than jumping between
rows.

---

## OpenCV connection

OpenCV provides reference implementations for both operations:

```cpp
cv::resize(source, resized, cv::Size{destination_width, destination_height},
           0.0, 0.0, cv::INTER_NEAREST);
cv::absdiff(manual, reference, difference);
```

Use these to validate—not replace—your manual implementation. A difference
image of all zeroes means the two outputs match exactly.

---

## Review quiz

<form class="quiz" data-answer="b" data-explanation="Nearest neighbor selects one existing source pixel for each output pixel; it does not average neighbors.">
  <fieldset>
    <legend>1. What does nearest-neighbor resizing do for each output pixel?</legend>
    <label><input type="radio" name="session4-q1" value="a"> Averages four source pixels.</label><br>
    <label><input type="radio" name="session4-q1" value="b"> Chooses one source pixel.</label><br>
    <label><input type="radio" name="session4-q1" value="c"> Creates a random pixel.</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="c" data-explanation="Destination coordinate 3 maps to 3 × 2 / 4, which is 1 with integer division.">
  <fieldset>
    <legend>2. Which source coordinate does destination coordinate 3 choose when resizing 2 values to 4?</legend>
    <label><input type="radio" name="session4-q2" value="a"> 0</label><br>
    <label><input type="radio" name="session4-q2" value="b"> 2</label><br>
    <label><input type="radio" name="session4-q2" value="c"> 1</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="a" data-explanation="Padding changes the distance between row starts, so the offset must use stride rather than visible width.">
  <fieldset>
    <legend>3. Which value finds the start of a padded row?</legend>
    <label><input type="radio" name="session4-q3" value="a"> Stride</label><br>
    <label><input type="radio" name="session4-q3" value="b"> Width</label><br>
    <label><input type="radio" name="session4-q3" value="c"> Channel count only</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="b" data-explanation="Absolute difference is zero when matching values are identical.">
  <fieldset>
    <legend>4. What does a zero in an absolute-difference image mean?</legend>
    <label><input type="radio" name="session4-q4" value="a"> The source image is empty.</label><br>
    <label><input type="radio" name="session4-q4" value="b"> The two corresponding values match.</label><br>
    <label><input type="radio" name="session4-q4" value="c"> The pixel is always black.</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="c" data-explanation="A timing result is meaningful only when compared under the same conditions; it is not a portable fixed target.">
  <fieldset>
    <legend>5. Why is one timing result not a universal performance score?</legend>
    <label><input type="radio" name="session4-q5" value="a"> Clocks cannot measure code.</label><br>
    <label><input type="radio" name="session4-q5" value="b"> Nearest neighbor has no loops.</label><br>
    <label><input type="radio" name="session4-q5" value="c"> Hardware and background work change the measurement.</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

---

## Completion check

- Map one destination coordinate to its source coordinate by hand.
- Compile and run all four solution files.
- Explain why a padded row needs stride.
- Answer all five quiz questions correctly.

Next: return to the [Module 1 overview](index.md) before starting Session 5.

---

## New C++ concepts

| C++ feature | Meaning here |
| --- | --- |
| Nested `for` loops | The outer loop visits destination rows; the inner loop visits every column in that row. |
| Integer division | The resize mapping drops a fractional coordinate, selecting the source pixel at the lower coordinate. |
| `std::array<T, N> result{}` | Creates fixed-size output storage with every value initialized to zero. |
| Return by value | `resize_nearest` and `absolute_difference` return a new small array. C++ handles this efficiently. |
| `std::chrono::steady_clock` | A monotonic clock suitable for measuring elapsed time; unlike wall time, it does not jump when the system clock changes. |
| `auto` | Lets the compiler infer a type. The timing example uses it because the clock time-point type is verbose. |
| `assert(condition)` | Verifies exact resize corners, stride offsets, and difference values. |
