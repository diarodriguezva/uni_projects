package robot;

import com.kuka.common.ThreadUtil;
import com.kuka.roboticsAPI.controllerModel.sunrise.ResumeMode;
import com.kuka.roboticsAPI.controllerModel.sunrise.SunriseController;
import com.kuka.roboticsAPI.controllerModel.sunrise.SunriseExecutionService;

public class ExecutionController {

	private RobotController controller = RobotController.getInstance();

	private SunriseController cabinet = controller.getCabinet();

	private SunriseExecutionService sunExecService = (SunriseExecutionService) cabinet.getExecutionService();

	public ExecutionController() {
		// we are always in T1, so no pause needed
		// sunExecService.startPause();
	}

	/**
	 * Resume exection.
	 */
	public void resume() {
		sunExecService.unblockExecutionForBrakeTest();
		sunExecService.resumeExecution(ResumeMode.OnPath);
	}

	/**
	 * Pause execution.
	 */
	public void pause() {
		sunExecService.startPause();
		sunExecService.blockExecutionForBrakeTest();
	}

	/**
	 * Abort current movement and start pause. Still often buggy!
	 */
	public void abort() {
		sunExecService.startPause();
		if (sunExecService.getActiveMotionContainerCount() > 0) {
			sunExecService.resumeExecution(ResumeMode.OnPath);
			ThreadUtil.milliSleep(100);
			sunExecService.cancelAll();
		}
		cabinet.acknowledgeError();
		sunExecService.blockExecutionForBrakeTest();
		sunExecService.unblockExecutionForBrakeTest();
		sunExecService.startPause();

		System.out.println("Abort finished");
	}

}