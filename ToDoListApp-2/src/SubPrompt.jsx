import React from 'react'
import './SubPrompt.css'

const SubPrompt = (props) => {

  const handleSubInput = (event) => {
    if (event.keyCode == 13){
      props.setSub(r => [...r, event.target.value])
      event.target.value=''
      props.setCounter(props.counter + 1)
      props.setTracker(r => [...r, props.counter])
    }
    props.setVal(event.target.keyCode)
  }

  return (
    <div>
      <input className="sub" type='text' value={props.val} placeholder="Enter a sub task..." onKeyDown={handleSubInput}/>
    </div>
  )
}

export default SubPrompt