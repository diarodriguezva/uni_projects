package de.tum.i6.cogsys.srvs;

import org.ros.exception.RemoteException;
import org.ros.exception.ServiceNotFoundException;
import org.ros.node.ConnectedNode;
import org.ros.node.service.ServiceClient;
import org.ros.node.service.ServiceResponseListener;
import org.smerobotics.util.srv.ServiceRequestBuilderFactory;

import speech_recognition_srvs.TurnOff;
import speech_recognition_srvs.TurnOffRequest;
import speech_recognition_srvs.TurnOffResponse;

public class TurnOffMicRequestBuilderFactory extends ServiceRequestBuilderFactory {

	public static final String SERVICE_NAME_TURN_OFF = "speech_recognition/turn_off";
	private ServiceClient<TurnOffRequest, TurnOffResponse> clientTurnOffMic;

	private final Object sync = new Object();
	private volatile boolean responsePending = false;
	
	@Override
	public synchronized void addServiceClients(ConnectedNode connectedNode) {

		if (clientTurnOffMic == null) {

			boolean found = false;

			while (!found) {

				try {

					clientTurnOffMic = connectedNode.newServiceClient(
							SERVICE_NAME_TURN_OFF,
							TurnOff._TYPE);

					found = true;

					System.out.println("    Found service '"
							+ SERVICE_NAME_TURN_OFF
							+ "'. (type: "
							+ TurnOff._TYPE + ")");

				} catch (ServiceNotFoundException e) {

					System.out.println("  Waiting for service '"
							+ SERVICE_NAME_TURN_OFF
							+ "' to start up. (type: "
							+ TurnOff._TYPE + ")");

					try {
						Thread.sleep(3000);
					} catch (InterruptedException ie) {
					}

				}

			}

		}

	}

	@Override
	public synchronized void removeServiceClients() {

		if (clientTurnOffMic != null) {

			clientTurnOffMic.shutdown();
			clientTurnOffMic = null;

			System.out.println("  Shutdown service client '"
					+ SERVICE_NAME_TURN_OFF
					+ "'. (type: "
					+ TurnOff._TYPE + ")");

		}

	}

	public void call() {

		TurnOffRequest req = clientTurnOffMic.newMessage();

		synchronized (sync) {

			responsePending = true;

			clientTurnOffMic.call(req, new ServiceResponseListener<TurnOffResponse>() {

				@Override
				public void onSuccess(TurnOffResponse response) {

					synchronized (sync) {
						responsePending = false;
						sync.notifyAll();
					}

				}

				@Override
				public void onFailure(RemoteException e) {

					synchronized (sync) {
						responsePending = false;
						sync.notifyAll();
					}

				}

			});

			while (responsePending) {
				try {
					sync.wait();
				} catch (InterruptedException e1) {
				}
			}

		}

	}

}
