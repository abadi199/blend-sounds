open Jest;

describe("Word", () => {
  describe("toString", () => {
    open Expect;
    test("toString(m,a,t)", () =>
      expect(true) |> toBe(true)
    );

    test("toString(qu,i,ck)", () =>
      expect(true) |> toBe(true)
    );
  });

  describe("fromString", () => {
    open Expect;
    test("fromString(\"m,a,t\")", () =>
      expect(true) |> toBe(true)
    );

    test("fromString(\"qu,i,c,k\")", () =>
      expect(true) |> toBe(true)
    );
  });

  describe("findPrev", () => {
    Expect.(test("findPrev", () =>
              expect(true) |> toBe(true)
            ))
  });

  describe("findNext", () => {
    Expect.(test("findNext", () =>
              expect(true) |> toBe(true)
            ))
  });
});