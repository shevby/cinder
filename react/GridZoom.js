import React, { useRef, useState } from 'react';
import { useGesture } from 'react-use-gesture';
import './GridZoom.css';

const GridZoom = () => {
  const [zoom, setZoom] = useState(1);
  const gridRef = useRef();
  const minZoom = 0.5; // Set the minimum zoom value

  const bind = useGesture(
    {
      onPinch: ({ delta, origin }) => {
        const newZoom = Math.max(minZoom, zoom + delta[0] / 100); // Use the minZoom value
        setZoom(newZoom);

        if (gridRef.current) {
          gridRef.current.style.transformOrigin = `${origin[0]}px ${origin[1]}px`;
        }
      },
    },
    { domTarget: gridRef }
  );

  const cells = [];
  for (let i = 0; i < 100; i++) {
    for (let j = 0; j < 100; j++) {
      cells.push(<div key={`${i}-${j}`} className="grid-cell" />);
    }
  }

  return (
    <div
      ref={gridRef}
      className="grid-container"
      style={{
        transform: `scale(${zoom})`,
      }}
      {...bind()}
    >
      {cells}
    </div>
  );
};

export default GridZoom;
