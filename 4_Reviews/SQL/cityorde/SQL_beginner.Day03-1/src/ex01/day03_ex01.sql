SELECT id AS menu_id
FROM menu
WHERE id NOT IN (SELECT menu_id FROM person_order WHERE menu_id = menu.id)
ORDER BY 1;