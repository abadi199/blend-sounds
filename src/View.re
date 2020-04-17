type display =
  | DisplayPlay;

type state = {
  display,
  distanceInPct: int,
  word: Word.state,
};

let initialState = {
  display: DisplayPlay,
  distanceInPct: 100,
  word: Word.initialState,
};

let str = React.string;

type action =
  | UpdateDistance(int)
  | WordAction(Word.action);

let reducer = (state, action) => {
  switch (action) {
  | UpdateDistance(distance) => {...state, distanceInPct: distance}
  | WordAction(wordAction) => {
      ...state,
      word: Word.reducer(state.word, wordAction),
    }
  };
};

[@react.component]
let make = (~dispatch, ~state) => {
  module ViewWord = {
    [@react.component]
    let make = () => {
      <Word
        distance={state.distanceInPct}
        state={state.word}
        dispatch={wordAction => dispatch(WordAction(wordAction))}
      />;
    };
  };

  switch (state.display) {
  | DisplayPlay =>
    <div className="play">
      <ViewWord />
      <input
        className="distance-slider"
        type_="range"
        name="distance"
        value={Js.Int.toString(state.distanceInPct)}
        onChange={_evt => {
          let value: int = ReactEvent.Form.target(_evt)##value;
          dispatch(UpdateDistance(value));
        }}
      />
    </div>
  };
};