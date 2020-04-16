open Sound;

type word = (sound, sound);

let toString = ((first, second): word): string => {
  Sound.toString(first) ++ "," ++ Sound.toString(second);
};

let fromString = (word: string): option(word) => {
  let split = word |> String.split_on_char(',');
  if (List.length(split) == 2) {
    Some((
      List.nth(split, 0) |> Sound.fromString,
      List.nth(split, 1) |> Sound.fromString,
    ));
  } else {
    None;
  };
};
let rec findPrev: (list(word), word) => option(word) =
  (words, word) => {
    let wordStr = toString(word);
    switch (words) {
    | [] => None
    | [_] => None
    | [a, b, ..._rest] when toString(b) == wordStr => Some(a)
    | [_, ...rest] => findPrev(rest, word)
    };
  };

let rec findNext: (list(word), word) => option(word) =
  (words, word) => {
    let wordStr = toString(word);
    switch (words) {
    | [] => None
    | [_] => None
    | [a, b, ..._rest] when toString(a) == wordStr => Some(b)
    | [_, ...rest] => findNext(rest, word)
    };
  };

let str = React.string;

let calculateWidth = (): int => {
  let innerWidth: int = [%bs.raw {|window.innerWidth|}];
  let wordsWidth = [%bs.raw
    {|
    Array
      .from(document.getElementsByClassName("sound"))
      .map(function(elem) { return elem.getBoundingClientRect().width; })
      .reduce(function(a,b) { return a + b; }, 0)
|}
  ];
  innerWidth - wordsWidth;
};

[@react.component]
let make = (~word: word, ~distance: int) => {
  let (first, second) = word;
  let width = Js.Int.toString(calculateWidth() * distance / 100) ++ "px";

  <div className="word">
    <Sound sound=first alignment=Right />
    <span className="gap" style={ReactDOMRe.Style.make(~width, ())} />
    <Sound sound=second alignment=Left />
  </div>;
};