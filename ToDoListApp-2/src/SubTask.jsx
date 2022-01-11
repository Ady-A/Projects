import React from 'react'
import './SubTask.css'


const SubTask = (props) => {

  console.log(props.checkList)

  const listUpdater = (event) => {
    if(event.target.checked){
      props.setCheckList(r => [...r, props.val])
    }
    else if (!event.target.checked){
      props.setCheckList(props.checkList.filter(sub => sub !== props.val))
    }
  }

  if(props.checkList.length/props.subTracker.length==1){
      props.setCircleState("Green")
  }
  else if(props.checkList.length/props.subTracker.length>=0.5){
    props.setCircleState("#99ff66")
  }
  else if(props.checkList.length/props.subTracker.length>=0.25){
    props.setCircleState("#ffff66")
  }
  else{props.setCircleState("Red")}

    return(
        <div className="subTask">
            <input type="checkbox" onClick={listUpdater} value={props.val} checked={props.checkList.includes(props.val)}/>{props.subName}
        </div>
    )
}

export default SubTask