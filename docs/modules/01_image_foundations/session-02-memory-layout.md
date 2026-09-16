# Session 2: Image Memory Layout

**Time:** about 2–2.5 hours  
**Prerequisite:** complete [Session 1](session-01-pixels.md).

This session turns the row-major model into a safe image view. Every hands-on
exercise uses only C++20, fixed data, and a single source file.

---

## Goals

By the end of this session, you can:

- Explain contiguous storage and why a whole image can be one flat sequence.
- Distinguish image width from stride.
- Locate an interleaved BGR channel with row, column, and channel indexes.
- Read an `ImageView` that borrows storage without copying it.

---

## Core idea: width is not always stride

For a tightly packed grayscale image with width `3`, the second row begins
after three values. Width and stride are both `3`:

```text
row 0: 10  11  12
row 1: 20  21  22
storage: 10  11  12  20  21  22
```

Some image formats add unused padding after each row. This makes rows start at
a larger distance than their visible width:

```text
width = 3, stride = 5 elements
row 0: 10  11  12  pad  pad
row 1: 20  21  22  pad  pad
storage: 10  11  12  -1   -1   20  21  22  -1   -1
```

The visible pixel at `(1, 2)` is therefore at `1 * stride + 2 = 7`, not at
`1 * width + 2 = 5`. In real image libraries, stride is usually measured in
**bytes**; the exercises use `int` elements so the arithmetic is easier to
see.

For interleaved BGR storage, every pixel has adjacent blue, green, and red
values. Its first channel is:

```text
row * stride + column * channels
```

Then add `0` for blue, `1` for green, or `2` for red.

---

## Build commands

Each file below is complete. From the repository root, compile one with:

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic \
  modules/01_image_foundations/session_02/exercises/01_contiguous_row.cpp \
  -o /tmp/01_contiguous_row
/tmp/01_contiguous_row
```

Starter programs compile but intentionally fail an `assert` until you replace
their `TODO`. Solution programs compile and run successfully with the same
command after replacing `exercises` with `solutions`.

---

## Understanding `std::span`

`std::span<T>` is a **view**, not a container. Conceptually, it stores only two
pieces of information:

```text
address of first value + number of values in the view
```

It does not allocate memory and it does not copy pixel values. This makes a
span useful when one large image buffer already exists and code needs to look
at only one row, region, or channel range.

```cpp
const std::array<int, 6> storage{10, 11, 12, 20, 21, 22};
const std::span<const int> pixels{storage};
const std::span<const int> row_1 = pixels.subspan(3, 3);
```

`pixels` views all six values. `row_1` starts three values later and views the
next three values:

```text
storage: 10  11  12 | 20  21  22
pixels:  [---------------------]
row_1:              [----------]
```

Changing a value through a writable span changes the original storage because
there is only one buffer. This lesson uses `std::span<const int>`, so reads are
allowed but writes through the view are rejected by the compiler.

### The lifetime rule

The array or vector that owns the values must stay alive, and stay at the same
memory address, for as long as a span views it. A span over a local array must
not be returned from its function. Likewise, growing a `std::vector` can move
its storage and invalidate existing spans. Use a span for short-lived access to
storage owned elsewhere; use `std::vector` or `std::array` when you need to own
the values.

---

## Exercise 1: View a contiguous row

The storage is a 2 × 3 grayscale image. Use `std::span::subspan` to make a
non-owning view over row `1`, whose values are `20`, `21`, and `22`.

```cpp
--8<-- "modules/01_image_foundations/session_02/exercises/01_contiguous_row.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_02/solutions/01_contiguous_row.cpp"
```

</details>

---

## Exercise 2: Respect stride

The buffer has two padding elements after every visible row. Compute the
offset of pixel `(1, 2)` using `stride`, not `width`.

```cpp
--8<-- "modules/01_image_foundations/session_02/exercises/02_stride.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_02/solutions/02_stride.cpp"
```

</details>

---

## Exercise 3: Read an interleaved BGR `ImageView`

Complete `ImageView::at`. It must calculate the offset of a BGR channel using
the row, column, channel count, and stride. Pixel `(1, 0)` has BGR values
`7`, `8`, and `9`.

```cpp
--8<-- "modules/01_image_foundations/session_02/exercises/03_image_view.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_02/solutions/03_image_view.cpp"
```

</details>

---

## OpenCV connection

`cv::Mat` exposes the same layout facts:

| Need | `cv::Mat` member |
| --- | --- |
| Visible columns | `image.cols` |
| Channels per pixel | `image.channels()` |
| Bytes between row starts | `image.step` |
| Pointer to the first byte | `image.data` |
| Tightly packed check | `image.isContinuous()` |

For an 8-bit BGR image, one tightly packed row normally needs
`image.cols * image.channels()` bytes. Do not replace `image.step` with that
calculation unless `image.isContinuous()` and the layout guarantee it is safe.

---

## Review quiz

<form class="quiz" data-answer="b" data-explanation="Contiguous storage places each value immediately after the previous value, so a complete image can use one flat sequence.">
  <fieldset>
    <legend>1. What does contiguous image storage mean?</legend>
    <label><input type="radio" name="session2-q1" value="a"> Every row is stored in a separate file.</label><br>
    <label><input type="radio" name="session2-q1" value="b"> Values are stored next to each other in one sequence.</label><br>
    <label><input type="radio" name="session2-q1" value="c"> Every pixel has exactly one channel.</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="c" data-explanation="Stride is the distance from one row start to the next; padding can make it larger than the visible width.">
  <fieldset>
    <legend>2. What is an image stride?</legend>
    <label><input type="radio" name="session2-q2" value="a"> The number of color channels.</label><br>
    <label><input type="radio" name="session2-q2" value="b"> The total number of image pixels.</label><br>
    <label><input type="radio" name="session2-q2" value="c"> The distance between the starts of consecutive rows.</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="a" data-explanation="The second row begins at 1 × 5, then column 2 moves two more elements: 7.">
  <fieldset>
    <legend>3. With stride 5, what is the offset of grayscale pixel (1, 2)?</legend>
    <label><input type="radio" name="session2-q3" value="a"> 7</label><br>
    <label><input type="radio" name="session2-q3" value="b"> 5</label><br>
    <label><input type="radio" name="session2-q3" value="c"> 15</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="b" data-explanation="BGR has three values per pixel, and channel 0 is blue.">
  <fieldset>
    <legend>4. In interleaved BGR storage, which channel index selects blue?</legend>
    <label><input type="radio" name="session2-q4" value="a"> 1</label><br>
    <label><input type="radio" name="session2-q4" value="b"> 0</label><br>
    <label><input type="radio" name="session2-q4" value="c"> 3</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="c" data-explanation="std::span borrows an existing contiguous range; it does not own or copy the pixels.">
  <fieldset>
    <legend>5. What does std::span provide in Exercise 1?</legend>
    <label><input type="radio" name="session2-q5" value="a"> A new copied image buffer.</label><br>
    <label><input type="radio" name="session2-q5" value="b"> A dynamically growing pixel container.</label><br>
    <label><input type="radio" name="session2-q5" value="c"> A non-owning view of existing contiguous values.</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

---

## Completion check

- Explain why width and stride differ when rows have padding.
- Calculate an interleaved BGR channel offset by hand.
- Compile and run all three solution files.
- Answer all five quiz questions correctly.

Next: return to the [Module 1 overview](index.md) before starting Session 3.

---

## C++ concepts used in this session

| C++ feature | Meaning here |
| --- | --- |
| `std::span<T>` | A lightweight, non-owning view over contiguous values. It borrows storage, so the original array or vector must outlive the span. |
| `span.subspan(offset, count)` | Produces a smaller view starting at `offset` with `count` values; Exercise 1 uses it to view one row without copying. |
| `struct` | Groups related data into one type. `ImageView` groups storage and its layout metadata. |
| Member function | A function inside a `struct`. `ImageView::at` uses the view's own width, channels, stride, and storage. |
| `const` after a function | Promises that the member function will not change the `ImageView`; `at(...) const` is a read-only operation. |
| `[[nodiscard]]` | Asks the compiler to warn when a returned value is ignored. A pixel read should normally be used. |
| `static_cast<void>(value)` | Explicitly marks an unused value in the unfinished starter, preventing compiler warnings before the TODO is implemented. |
| `std::array<T, N>` | Fixed-size storage used to make every exercise self-contained. |
| `assert(condition)` | A runnable correctness check. Each starter fails one until its TODO computes the correct offset. |
