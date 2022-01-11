import React from 'react'
import './AddTask.css'

const AddTask = (props) => {
  let counter = 0
  const addMainTask = () => {
    props.setAdding(!props.adding)
  }
  return(
    <div>
      <button className="AddEventButton" onClick={addMainTask}>+</button>
    </div>
   )
}

export default AddTask