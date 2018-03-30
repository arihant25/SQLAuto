SELECT * 
FROM CHAIR, (SELECT * 
FROM DESK, (SELECT * 
FROM SOMETHING, APPLE 
WHERE SOMETHING.fibre = APPLE.fibre) as joinedTable_1 
WHERE DESK.metal = joinedTable_1.metal) as joinedTable_2 
WHERE CHAIR.wood = joinedTable_2.wood