-- Update titles to proper title case
UPDATE shows
SET title =
  CASE
    WHEN title LIKE 'ADVENTURE TIME%' THEN 'Adventure Time'
    WHEN title LIKE 'ARROW%' THEN 'Arrow'
    WHEN title LIKE 'AVATAR: THE LAST AIRBENDER%' THEN 'Avatar: The Last Airbender'
    WHEN title LIKE 'BROOKLYN NINE-NINE%' THEN 'Brooklyn Nine-Nine'
    WHEN title LIKE 'COMMUNITY%' THEN 'Community'
    WHEN title LIKE 'FAMILY GUY%' THEN 'Family Guy'
    WHEN title LIKE 'FRIENDS%' THEN 'Friends'
    WHEN title LIKE 'GAME OF THRONES%' THEN 'Game of Thrones'
    WHEN title LIKE 'GILMORE GIRLS%' THEN 'Gilmore Girls'
    WHEN title LIKE 'GREY’S ANATOMY%' THEN 'Grey’s Anatomy'
    WHEN title LIKE 'HOW I MET YOUR MOTHER%' THEN 'How I Met Your Mother'
    WHEN title LIKE 'IT’S ALWAYS SUNNY IN PHILADELPHIA%' THEN 'It’s Always Sunny in Philadelphia'
    WHEN title LIKE 'PARKS AND RECREATION%' THEN 'Parks and Recreation'
    WHEN title LIKE 'SHERLOCK%' THEN 'Sherlock'
    WHEN title LIKE 'SQUID GAME%' THEN 'Squid Game'
    WHEN title LIKE 'THE BACHELORETTE%' THEN 'The Bachelorette'
    WHEN title LIKE 'THE CROWN%' THEN 'The Crown'
    WHEN title LIKE 'THE OFFICE%' THEN 'The Office'
    WHEN title LIKE 'THE QUEEN’S GAMBIT%' THEN 'The Queen’s Gambit'
    WHEN title LIKE 'THE UNTAMED%' THEN 'The Untamed'
    ELSE title
  END;


UPDATE shows
SET title =
  CASE
    WHEN title LIKE 'BROOKLYN NINE-NINE%' OR title 'B99'THEN 'Brooklyn Nine-Nine'
    WHEN title LIKE 'Got' THEN 'Game of Thrones'
    WHEN title LIKE 'GREY’S ANATOMY%' THEN 'Grey’s Anatomy'
    WHEN title LIKE 'IT’S ALWAYS SUNNY IN PHILADELPHIA%' THEN 'It’s Always Sunny in Philadelphia'
    WHEN title LIKE 'PARKS AND RECREATION%' THEN 'Parks and Recreation'
    WHEN title LIKE 'THE OFFICE%' THEN 'The Office'
    ELSE title
  END;


