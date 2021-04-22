/*-
 * #%L
 * Codenjoy - it's a dojo-like platform from developers to developers.
 * %%
 * Copyright (C) 2018 Codenjoy
 * %%
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/gpl-3.0.html>.
 * #L%
 */
using System.Collections.Generic;

namespace Loderunner.Api
{
    internal class ElementSet
    {
        internal static readonly HashSet<BoardElement> Hero = new HashSet<BoardElement>
        {
            BoardElement.HeroDie,
            BoardElement.HeroDrillLeft,
            BoardElement.HeroDrillRight,
            BoardElement.HeroFallRight,
            BoardElement.HeroFallLeft,
            BoardElement.HeroLadder,
            BoardElement.HeroLeft,
            BoardElement.HeroRight,
            BoardElement.HeroPipeLeft,
            BoardElement.HeroPipeRight,
            BoardElement.HeroShadowDie,
            BoardElement.HeroShadowDrillLeft,
            BoardElement.HeroShadowDrillRight,
            BoardElement.HeroShadowFallLeft,
            BoardElement.HeroShadowFallRight,
            BoardElement.HeroShadowLadder,
            BoardElement.HeroShadowLeft,
            BoardElement.HeroShadowRight,
            BoardElement.HeroShadowPipeLeft,
            BoardElement.HeroShadowPipeRight,
        };

        internal static readonly HashSet<BoardElement> Ladder = new HashSet<BoardElement>
        {
            BoardElement.Ladder,
            BoardElement.HeroLadder,
            BoardElement.OtherHeroLadder,
            BoardElement.EnemyLadder,
            BoardElement.HeroShadowLadder,
            BoardElement.OtherHeroShadowLadder
        };

        internal static readonly HashSet<BoardElement> Enemy = new HashSet<BoardElement>
        {
            BoardElement.EnemyLadder,
            BoardElement.EnemyLeft,
            BoardElement.EnemyPipeLeft,
            BoardElement.EnemyPipeRight,
            BoardElement.EnemyRight,
            BoardElement.EnemyPit
        };

        internal static readonly HashSet<BoardElement> OtherHero = new HashSet<BoardElement>
        {
            BoardElement.OtherHeroLadder,
            BoardElement.OtherHeroLeft,
            BoardElement.OtherHeroPipeLeft,
            BoardElement.OtherHeroPipeRight,
            BoardElement.OtherHeroRight,
            BoardElement.OtherHeroShadowLadder,
            BoardElement.OtherHeroShadowLeft,
            BoardElement.OtherHeroShadowRight,
            BoardElement.OtherHeroShadowPipeLeft,
            BoardElement.OtherHeroShadowPipeRight,
            BoardElement.OtherHeroShadowFallLeft,
            BoardElement.OtherHeroShadowFallRight,
            BoardElement.OtherHeroShadowDrillLeft,
            BoardElement.OtherHeroShadowDrillRight,
            BoardElement.OtherHeroFallLeft,
            BoardElement.OtherHeroFallRight,
            BoardElement.OtherHeroDrillLeft,
            BoardElement.OtherHeroDrillRight
        };

        internal static readonly HashSet<BoardElement> Pipe = new HashSet<BoardElement>
        {
            BoardElement.Pipe,
            BoardElement.HeroPipeLeft,
            BoardElement.HeroPipeRight,
            BoardElement.OtherHeroPipeLeft,
            BoardElement.OtherHeroPipeRight,
            BoardElement.EnemyPipeLeft,
            BoardElement.EnemyPipeRight,
            BoardElement.HeroShadowPipeLeft,
            BoardElement.HeroShadowPipeRight,
            BoardElement.OtherHeroShadowPipeLeft,
            BoardElement.OtherHeroShadowPipeRight
        };

        internal static readonly HashSet<BoardElement> Wall = new HashSet<BoardElement>
        {
            BoardElement.Brick,
            BoardElement.UndestroyableWall
        };

        internal static readonly HashSet<BoardElement> Gold = new HashSet<BoardElement>
        {
            BoardElement.YellowGold,
            BoardElement.GreenGold,
            BoardElement.RedGold
        };

        internal static readonly HashSet<BoardElement> Shadow = new HashSet<BoardElement>
        {
            BoardElement.OtherHeroShadowLadder,
            BoardElement.OtherHeroShadowLeft,
            BoardElement.OtherHeroShadowRight,
            BoardElement.OtherHeroShadowPipeLeft,
            BoardElement.OtherHeroShadowPipeRight,
            BoardElement.OtherHeroShadowFallLeft,
            BoardElement.OtherHeroShadowFallRight,
            BoardElement.OtherHeroShadowDrillLeft,
            BoardElement.OtherHeroShadowDrillRight,
            BoardElement.HeroShadowDrillLeft,
            BoardElement.HeroShadowDrillRight,
            BoardElement.HeroShadowLadder,
            BoardElement.HeroShadowLeft,
            BoardElement.HeroShadowRight,
            BoardElement.HeroShadowFallLeft,
            BoardElement.HeroShadowFallRight,
            BoardElement.HeroShadowPipeLeft,
            BoardElement.HeroShadowPipeRight,
            BoardElement.HeroShadowDie
        };
    }
}
