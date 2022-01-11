import React, { useState } from 'react'
import SubTask from './SubTask'
import SubPrompt from './SubPrompt'
import './SubWrapper.css'

const SubWrapper = (props) => {

  return(
    <div className="sub-wrapper">
      {props.subTracker.map(num => <SubTask subName={props.subTasks[num]} checkList={props.checkList} setCheckList={props.setCheckList} val={props.subTracker[num]} setCircleState={props.setCircleState} subTracker={props.subTracker}/>)}
      
      <SubPrompt setTracker={props.setSubTracker} counter={props.counterSub} setCounter={props.setCounterSub} val={props.subPromptVal} setVal={props.setSubPromptVal} setSub={props.setSubTasks}/>
    </div>
  )
}

export default SubWrapper