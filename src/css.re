/* TODO how can we properly format a float? */
let fmtfloat n => string_of_float n ^ "0";

let translate3d (x, y, z) =>
  "translate3d(" ^ fmtfloat x ^ "px, " ^ fmtfloat y ^ "px, " ^ fmtfloat z ^ "px)";

/* ironically wants a 4d matrix */
let matrix3d ((a, b, c, d), (e, f, g, h), (i, j, k, l), (m, n, o, p)) => {
  let fmt n => fmtfloat n ^ ", ";
  "matrix3d(" ^
  fmt a ^
  fmt b ^
  fmt c ^
  fmt d ^
  fmt e ^
  fmt f ^ fmt g ^ fmt h ^ fmt i ^ fmt j ^ fmt k ^ fmt l ^ fmt m ^ fmt n ^ fmt o ^ fmtfloat p ^ ")"
};
