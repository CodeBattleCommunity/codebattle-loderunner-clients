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
using System;
using System.Collections.Generic;
using System.Linq;

namespace Loderunner.Api
{
    public class GameBoard
    {
        private readonly BoardElement[] HeroIdentifiers =
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

        private readonly BoardElement[] LadderIdentifiers =
        {
            BoardElement.Ladder,
            BoardElement.HeroLadder,
            BoardElement.OtherHeroLadder,
            BoardElement.EnemyLadder,
            BoardElement.HeroShadowLadder,
            BoardElement.OtherHeroShadowLadder
        };

        private readonly BoardElement[] EnemyIdentifiers =
        {
            BoardElement.EnemyLadder,
            BoardElement.EnemyLeft,
            BoardElement.EnemyPipeLeft,
            BoardElement.EnemyPipeRight,
            BoardElement.EnemyRight,
            BoardElement.EnemyPit
        };

        private readonly BoardElement[] OtherHeroIdentifiers =
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
            BoardElement.OtherHeroShadowPipeRight
        };

        private readonly BoardElement[] PipeIdentifiers =
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

        private readonly BoardElement[] WallIdentifiers =
        {
            BoardElement.Brick,
            BoardElement.UndestroyableWall
        };

        private readonly BoardElement[] GoldIdentifiers =
        {
            BoardElement.YellowGold,
            BoardElement.GreenGold,
            BoardElement.RedGold
        };

        private readonly BoardElement[] ShadowIdentifiers =
        {
            BoardElement.OtherHeroShadowLadder,
            BoardElement.OtherHeroShadowLeft,
            BoardElement.OtherHeroShadowRight,
            BoardElement.OtherHeroShadowPipeLeft,
            BoardElement.OtherHeroShadowPipeRight,
            BoardElement.HeroShadowDrillLeft,
            BoardElement.HeroShadowDrillRight,
            BoardElement.HeroShadowLadder,
            BoardElement.HeroShadowLeft,
            BoardElement.HeroShadowRight,
            BoardElement.HeroShadowFallLeft,
            BoardElement.HeroShadowFallRight,
            BoardElement.HeroShadowPipeLeft,
            BoardElement.HeroShadowPipeRight
        };

        public GameBoard(string boardString)
        {
            BoardString = boardString.Replace("\n", "");
        }

        public string BoardString { get; }

        public int Size => (int)Math.Sqrt(BoardString.Length);

        /// <summary>
        /// Returns the list of points for the given element type.
        /// </summary>
        /// <param name="element"></param>
        /// <returns></returns>
        public List<BoardPoint> FindAll(params BoardElement[] element) => Enumerate(element).ToList();

        /// <summary>
        /// Returns the point where your hero is.
        /// </summary>
        public BoardPoint GetMyPosition() => EnumerateMap()
            .Single(point => HasElementAt(point, HeroIdentifiers));

        /// <summary>
        /// Returns a BoardElement object at coordinates x,y.
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        public BoardElement GetAt(int x, int y) => (BoardElement)BoardString[GetShiftByPoint(x, y)];

        /// <summary>
        /// Returns True if BoardElement is at x,y coordinates.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="element"></param>
        /// <returns></returns>
        public bool HasElementAt(int x, int y, BoardElement element)
        {
            if (IsOutOfBoard(x, y))
            {
                return false;
            }

            return GetAt(x, y) == element;
        }

        /// <summary>
        /// Returns true if barrier is at x,y.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool IsBarrierAt(int x, int y) => HasElementAt(x, y, WallIdentifiers);

        /// <summary>
        /// Returns False if your hero still alive.
        /// </summary>
        /// <returns></returns>
        public bool IsHeroDead() => BoardString.Contains((char)BoardElement.HeroDie);

        /// <summary>
        /// Return the list of points for other heroes.
        /// </summary>
        /// <returns></returns>
        public List<BoardPoint> GetEnemyPositions() => FindAll(EnemyIdentifiers);

        /// <summary>
        /// Returns the list of points for other heroes.
        /// </summary>
        /// <returns></returns>
        public List<BoardPoint> GetOtherHeroPositions() => FindAll(OtherHeroIdentifiers);

        /// <summary>
        /// Returns the list of points for elements with type BoardElement.TheShadowPill.
        /// </summary>
        /// <returns></returns>
        public List<BoardPoint> GetShadowPills() => FindAll(BoardElement.TheShadowPill);

        /// <summary>
        /// Returns the list of points for elements with type BoardElement.Portal.
        /// </summary>
        /// <returns></returns>
        public List<BoardPoint> GetPortals() => FindAll(BoardElement.Portal);

        /// <summary>
        /// Returns the list of walls element Points.
        /// </summary>
        /// <returns></returns>
        public List<BoardPoint> GetWallPositions() => FindAll(WallIdentifiers);

        /// <summary>
        /// Returns the set of ladder Points.
        /// </summary>
        /// <returns></returns>
        public List<BoardPoint> GetLadderPositions() => Enumerate(LadderIdentifiers).Distinct().ToList();

        /// <summary>
        /// Return the list of points for elements with types:
        /// BoardElement.YellowGold, BoardElement.GreenGold, BoardElement.RedGold
        /// </summary>
        /// <returns></returns>
        public List<BoardPoint> GetGoldPositions() => FindAll(GoldIdentifiers);

        /// <summary>
        /// Returns the set of pipe BoardPoints.
        /// </summary>
        /// <returns></returns>
        public List<BoardPoint> GetPipePositions() => FindAll(PipeIdentifiers);

        /// <summary>
        /// Returns the list of barriers Points.
        /// </summary>
        /// <returns></returns>
        public List<BoardPoint> GetBarriers() => Enumerate(WallIdentifiers).Distinct().ToList();

        /// <summary>
        /// Check if near exists element of chosen type.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="element"></param>
        /// <returns></returns>
        public bool IsNearToElement(int x, int y, BoardElement element)
        {
            if (IsOutOfBoard(x, y))
                return false;

            return EnumerateNeighbors(new BoardPoint(x, y))
                .Any(neighbor => HasElementAt(neighbor, element));
        }

        /// <summary>
        /// Returns True if enemy exists in current point.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool HasEnemyAt(int x, int y) => HasElementAt(x, y, EnemyIdentifiers);

        /// <summary>
        /// Returns True if other hero exists in current point.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool HasOtherHeroAt(int x, int y) => HasElementAt(x, y, OtherHeroIdentifiers);

        /// <summary>
        /// Returns True if wall exists in current point.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool HasWallAt(int x, int y) => HasElementAt(x, y, WallIdentifiers);

        /// <summary>
        /// Returns True if ladder exists in current point.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool HasLadderAt(int x, int y) => HasElementAt(x, y, LadderIdentifiers);

        /// <summary>
        /// Returns True if golf exists in current point.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool HasGoldAt(int x, int y) => HasElementAt(x, y, GoldIdentifiers);

        /// <summary>
        /// Returns True if pipe exists in current point.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool HasPipeAt(int x, int y) => HasElementAt(x, y, PipeIdentifiers);

        /// <summary>
        /// Returns True if shadow exists in current point.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool HasShadowAt(int x, int y) => HasElementAt(x, y, ShadowIdentifiers);

        /// <summary>
        /// Counts the number of occurrences of element nearby.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="element"></param>
        /// <returns></returns>
        public int GetCountElementsNearToPoint(int x, int y, BoardElement element)
        {
            if (IsOutOfBoard(x, y))
                return 0;

            return EnumerateNeighbors(new BoardPoint(x, y))
                .Count(neighbor => HasElementAt(neighbor, element));
        }

        public void PrintBoard()
        {
            for (int i = 0; i < Size; i++)
            {
                Console.WriteLine(BoardString.Substring(i * Size, Size));
            }
        }

        private IEnumerable<BoardPoint> EnumerateNeighbors(BoardPoint point)
        {
            yield return point.ShiftLeft();
            yield return point.ShiftRight();
            yield return point.ShiftTop();
            yield return point.ShiftBottom();
        }

        private IEnumerable<BoardPoint> EnumerateMap() => Enumerable
            .Range(0, Size * Size)
            .Select(GetPointByShift);

        public IEnumerable<BoardPoint> Enumerate(params BoardElement[] element) => EnumerateMap()
            .Where(point => HasElementAt(point, element));

        private bool HasElementAt(int x, int y, params BoardElement[] elements)
            => elements.Any(elem => HasElementAt(x, y, elem));

        private bool HasElementAt(BoardPoint point, params BoardElement[] elements)
        {
            return elements.Any(elem => HasElementAt(point.X, point.Y, elem));
        }

        private int GetShiftByPoint(BoardPoint point) => GetShiftByPoint(point.Y, point.X);

        private int GetShiftByPoint(int x, int y) => y * Size + x;

        private BoardPoint GetPointByShift(int shift) => new BoardPoint(shift % Size, shift / Size);

        private bool IsOutOfBoard(int x, int y) => x >= Size || y >= Size || x < 0 || y < 0;
    }
}
