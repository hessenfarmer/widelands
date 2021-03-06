dirname = path.dirname(__file__)

animations = {
   idle = {
      pictures = path.list_files(dirname .. "idle_??.png"),
      hotspot = { 11, 11 },
      fps = 20,
   },
   eating = {
      directory = dirname,
      basename = "idle", -- TODO(Nordfriese): Make animation
      hotspot = { 11, 11 },
      fps = 20,
   }
}

add_directional_animation(animations, "walk", dirname, "walk", {15, 14}, 20)

world:new_critter_type{
   name = "marten",
   descname = _ "Marten",
   editor_category = "critters_carnivores",
   attributes = { "eatable" },
   programs = {
      remove = { "remove" },
   },
   animations = animations,
   size = 2,
   reproduction_rate = 50,
   appetite = 20,
   carnivore = true,
}
