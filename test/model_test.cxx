#include "model.hxx"

#include <catch.hxx>


struct Test_access
{
    Model& m;

    //ge211::Timer player_timer = m.player_timer;
};

// TEST_CASE("Hitting an alien")
// {
//     Model m;
//     Test_access t{m};
//
//     double const dt = 1;
//     for(int i = 0; i < 200000; i++) {
//         m.on_frame(dt);
//     }
//
//     CHECK(m.active_player_lasers.empty());
//
//     CHECK(t.player_timer.elapsed_time().seconds() >= ge211::Duration(1.5).seconds());
//
//     m.player.x = 100;
//     m.player_shoot_laser();
//
//     CHECK_FALSE(m.active_player_lasers.empty());
////     m.aliens.clear();
// //     m.aliens.push_back({100, 200, m.config.alien_dims().width,
// //                         m.config.alien_dims().height});
// //

// /    Laser l = m.active_player_lasers[0];
//      l.center.y = 199;
//     m.on_frame(dt);
//
//     CHECK(l.hits_alien(m.aliens[0]));
//
//     m.on_frame(dt);
//
//     CHECK(m.game_over);
// }

// TEST_CASE("Player gets hit"){
//     Model m;
//
//     m.aliens.clear();
//     m.shields.clear();
//     m.aliens.push_back({m.player.x + m.player.width/2,
//                         m.player.y - 100, m.config.alien_dims().width,
//                         m.config.alien_dims().height});
//
//     // Puts a laser in, like alien_shoot_laser does minus the timer
//     m.alien_shoot_laser();
//     double const dt = 1;
//     for(int i = 0; i < 200000; i++) {
//         m.on_frame(dt);
//     }
//     m.player.x = 100;
//     AlienLaser l{m.aliens[0], m.config};
//     m.active_alien_lasers.push_back(l);
//     l.center.x = m.player.x;
//     l.center.y = m.player.y + l.height;
//     for(int i = 0; i < 200000; i++) {
//         m.on_frame(dt);
//     }
//     // Checks that the player got hit and their lives went down by 1
//     CHECK(m.player_lives == m.config.player_lives -1);
//     // Checks that the laser was destroyed after a hit
//
// }
TEST_CASE("Shield gets hit by players"){
    Model m;

    m.aliens.clear();
    m.shields.clear();
    m.shields.push_back({300,300, m.config});
    m.player.x = 300;
    m.player.y = 350;
    for(int i = 0; i < 200000; i++) {
        m.on_frame(1);
    }
    m.player_shoot_laser();

    //CHECK SHIELDS DESTROY AFTER PLAYER HIT;
    Laser l{m.player, m.config};
    m.active_player_lasers.push_back(l);
    m.active_player_lasers[0].center.y = m.player.y + m
            .active_player_lasers[0].height +1;
    m.active_player_lasers[0].center.x = m.player.x;
    CHECK(!m.active_player_lasers.empty());
    for(int i = 0; i < 200000; i++) {
    m.on_frame(1);
    }
    // Checks that the shield got hit and their lives went down by 1
    CHECK(m.shields[0].health == m.config.shield_hitpoints -1);
    // Checks that the laser was destroyed after a hit
    CHECK(m.active_player_lasers.empty());


}


TEST_CASE("Player lose by DEATH") {
    Model m;
//Some setup (this test checks the player will lose the game when they lose
// their lives)
    m.shields.clear();
    m.aliens.clear();
    m.aliens.push_back({100, 200, m.config.alien_dims().width,
                        m.config.alien_dims().height});
    m.player_lives = 1;
    m.player.x = 100;
    m.player.y = 100;
         for(int i = 0; i < 200000; i++) {
             m.on_frame(1);
         }
    m.alien_shoot_laser();
//  Creating new alien laser after cooldown has elapsed, then running frames
//  and checking for collision
    AlienLaser l{m.aliens[0], m.config};
    m.active_alien_lasers.push_back(l);
    m.active_alien_lasers[0].center.y = 100;
    for(int i = 0; i < 100; i++) {
        m.on_frame(1);
    }

    //Checks that player lives are 0
    CHECK(m.player_lives == 0);
    //Checks that the game is over
    CHECK(m.game_over);
    //Check that the player is set as the loser
    CHECK_FALSE(m.player_win);
}
TEST_CASE("alien movement check + lose at bottom") {

    //THIS TEST CHECKS THAT (1) ALIENS MOVE AND SHIFT DOWN PROPERLY, AND THAT
    // (2) THE PLAYER LOSES IF THE ALIENS REACH THE BOTTOM
    Model m;

    m.shields.clear();
    //Setting the alien right next to the edge of the screen
    m.aliens.push_back({1024 - m.config
    .alien_dims().width,
                        m.player.y - 1, m.config.alien_dims().width,
                        m.config.alien_dims().height});
    //This runs 100 frames, which will make sure that the alien moves to the
    // right AND that it shifts down at the edge
    for(int i = 0; i < 200000; i++) {
        m.on_frame(1);
    }
    //Check that the aliens are below the player (lose condition)
    CHECK(m.aliens[0].y_ + m.aliens[0].height_ >= m.player.y );
    //Check that the game is set to be over
    CHECK(m.game_over);

}
