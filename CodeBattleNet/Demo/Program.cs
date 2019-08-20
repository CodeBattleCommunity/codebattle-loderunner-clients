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
using Loderunner.Api;
using System;
using System.Threading;

namespace Demo
{
    class Program
    {
        const string ServerAddress = "localhost:8080";
        const string PlayerName = "<player-id>";
        const string AuthCode = "<code>";

        static void Main(string[] args)
        {
            // creating custom AI client
            var client = new LodeRunnerClient(ServerAddress, PlayerName, AuthCode);

            // starting thread with playing game
            client.Run(gameBoard =>
            {
                Random random = new Random(Environment.TickCount);
                return (LoderunnerAction)random.Next(3);

            });

            // waiting for any key
            Console.ReadKey();

            // on any key - asking AI client to stop.
            client.InitiateExit();
        }
    }
}
