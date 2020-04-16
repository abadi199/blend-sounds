open Word;

type display =
  | DisplayPlay;

type state = {
  word,
  display,
  distanceInPct: int,
};

let initialState = {
  word: (Sound.fromString("bl"), Sound.fromString("ock")),
  display: DisplayPlay,
  distanceInPct: 100,
};

let str = React.string;

type action =
  | EditWord(word);

let reducer = (state, action) => {
  switch (action) {
  | EditWord(word) => {word, display: DisplayPlay, distanceInPct: 100}
  };
};

[@react.component]
let make = (~dispatch, ~state) => {
  module ViewWord = {
    [@react.component]
    let make = (~word) => {
      <Word word distance=100 />;
    };
  };

  module ActionSection = {
    [@react.component]
    let make = () => {
      <div className="action">
        <button
          className="transparent-button edit-button"
          onClick={_evt => dispatch(EditWord(state.word))}
          title="Edit"
        />
      </div>;
    };
  };

  switch (state.display) {
  | DisplayPlay =>
    <div className="play">
      <ViewWord word={state.word} />
      <ActionSection />
    </div>
  };
};