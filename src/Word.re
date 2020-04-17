open Sound;

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

type state = {
  left: Sound.state,
  right: Sound.state,
};

let initialState = {
  left: Sound.initialState(Right),
  right: Sound.initialState(Left),
};

type action =
  | LeftAction(Sound.action)
  | RightAction(Sound.action);

let reducer = (state, action) => {
  switch (action) {
  | LeftAction(leftAction) => {
      ...state,
      left: Sound.reducer(state.left, leftAction),
    }
  | RightAction(rightAction) => {
      ...state,
      right: Sound.reducer(state.right, rightAction),
    }
  };
};

[@react.component]
let make = (~state, ~distance, ~dispatch) => {
  let width = Js.Int.toString(calculateWidth() * distance / 100) ++ "px";

  <div className="word">
    <Sound
      alignment=Right
      state={state.left}
      dispatch={soundAction => dispatch(LeftAction(soundAction))}
    />
    <span className="gap" style={ReactDOMRe.Style.make(~width, ())} />
    <Sound
      alignment=Left
      state={state.right}
      dispatch={soundAction => dispatch(RightAction(soundAction))}
    />
  </div>;
};