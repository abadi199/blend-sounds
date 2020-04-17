type display =
  | DisplayPlay;

type state = {
  display,
  distanceInPct: int,
};

let initialState = {display: DisplayPlay, distanceInPct: 100};

let str = React.string;

type action =
  | UpdateDistance(int);

let reducer = (state, action) => {
  switch (action) {
  | UpdateDistance(distance) => {...state, distanceInPct: distance}
  };
};

[@react.component]
let make = (~dispatch, ~state) => {
  module ViewWord = {
    [@react.component]
    let make = () => {
      <Word distance={state.distanceInPct} />;
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